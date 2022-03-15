#include "labellist.h"
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

typedef std::vector<LabelList::MsgType> MsgVec;

TEST(LabelListCheckPoint, AddPrint)
{
    MsgVec msgs = {"m0", "m1", "m2", "m3"};
    const size_t NUM_MSGS = 4;

    LabelList list1;
    for(size_t i = 0U; i != NUM_MSGS; i++)
    {
        list1.add(msgs[i]);
    }

    std::stringstream messageStream;
    list1.print(messageStream, "all");
    LabelList::MsgType msg;
    size_t i = 0;
    for( ; i < msgs.size() && messageStream >> msg; i++)
    {
        EXPECT_EQ(msgs[i], msg);
    }
    EXPECT_EQ(msgs.size(), i);
}

TEST(LabelListCheckPoint, LabelPrint)
{
    MsgVec msgs = {"m0", "m1", "m2", "m3"};
    const size_t NUM_MSGS = 4;

    LabelList list1;
    LabelList::MsgToken tokens[NUM_MSGS];
    // Add base messages and save tokens
    for(size_t i = 0U; i != NUM_MSGS; i++)
    {
        tokens[i] = list1.add(msgs[i]);
    }

    // Add a few sample labels
    list1.label(tokens[1], "a");
    list1.label(tokens[2], "b");
    list1.label(tokens[3], "a");
    list1.label(tokens[1], "c");

    // vector of vectors of expected messages for each label
    std::vector< LabelList::LabelType > labels = {"a", "b", "c"};
    std::vector< MsgVec > expectedMsgs = { {"m1", "m3"}, {"m2"}, {"m1"} };
    for(size_t i = 0; i < labels.size(); i++)
    {
        std::stringstream messageStream;
        list1.print(messageStream, labels[i]);
        LabelList::MsgType msg;
        size_t j = 0;
        for( ; j < expectedMsgs[i].size() && messageStream >> msg; j++)
        {
            EXPECT_EQ(expectedMsgs[i][j], msg);
        }
        EXPECT_EQ(expectedMsgs[i].size(), j);
    }
}

TEST(LabelListCheckPoint, MsgToken)
{
    MsgVec msgs = {"m0", "m1"};
    const size_t NUM_MSGS = 2;
    LabelList::MsgToken tokens[NUM_MSGS];

    LabelList list1;
    for(size_t i = 0U; i != NUM_MSGS; i++)
    {
        tokens[i] = list1.add(msgs[i]);
    }

    // Comparison and bool operator
    EXPECT_TRUE(tokens[0] == tokens[0]);
    EXPECT_FALSE(tokens[0] == tokens[1]);
    EXPECT_TRUE(tokens[0]);
    EXPECT_FALSE(list1.end());

    // Msg accessor/mutator 
    EXPECT_EQ("m0", tokens[0].msg());
    LabelList::MsgType newMsg = "new message";
    tokens[0].msg() = newMsg;
    EXPECT_EQ(newMsg, tokens[0].msg());
}
