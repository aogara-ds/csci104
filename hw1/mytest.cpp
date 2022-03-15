#include <iostream>
#include "labellist.h"
#include <gtest/gtest.h>
using namespace std;

int main()
{
    std::vector<LabelList::MsgType> msgs = {"m0", "m1"};
    const size_t NUM_MSGS = 2;
    LabelList::MsgToken tokens[NUM_MSGS];

    LabelList list1;
    for(size_t i = 0U; i != NUM_MSGS; i++)
    {
        tokens[i] = list1.add(msgs[i]);
    }
    std::cout << &tokens[0] << std::endl;

    // Comparison using bool operator
    std::cout << (tokens[0] != tokens[0]) << std::endl;
}

