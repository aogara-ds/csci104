#include "labellist.h"
#include <cassert>
#include <vector>
#include <algorithm>

// BIG TODOS:
// Remove
// Clear


// Complete - Do not alter
LabelList::MsgNode::MsgNode(const MsgType& msg)
    : msg_(msg)
{
    labelled_.push_back(true);
    next_.push_back(nullptr);
    prev_.push_back(nullptr);
}


// Complete - Do not alter
LabelList::MsgToken::MsgToken()
 : node_(nullptr), list_(nullptr)
{
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::MsgToken(MsgNode* node, LabelList* list)
    : node_(node), list_(list)
{
    // QUESTION: Why is MsgToken initializing 
    // before LabelList constructor is called?
    // For now, assume this is correct behavior. 
}

// To be completed - must adhere to any requirements in the .h file
// DONE
bool LabelList::MsgToken::operator==(const MsgToken& rhs) const
{
    return this->node_ == rhs.node_;
}

// Complete - Do not alter
bool LabelList::MsgToken::operator!=(const MsgToken& rhs) const
{
    return !operator==(rhs);
}

// To be completed - must adhere to any requirements in the .h file
// DONE
LabelList::MsgToken::operator bool() const
{
    return this->isValid();
}

// Complete - Do not alter
// isValid() checks whether node is a nullptr
bool LabelList::MsgToken::isValid() const
{
    return this->node_ != nullptr;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::next(const LabelType& label)
{
    size_t index = this->list_->findLabelIndex(label);
    
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->next_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::prev(const LabelType& label)
{
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->prev_[index];

    return *this;
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(const LabelType& label) const
{
    size_t index = this->list_->findLabelIndex(label);
    return isLabelMember(index);
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(size_t index) const
{
    return this->isValid() && 
            index != INVALID_LABEL &&
            this->node_->labelled_[index] ;
}

// To be completed - must adhere to any requirements in the .h file
// DONE
LabelList::MsgType const & LabelList::MsgToken::msg() const
{
    // Throws a logic error if the token does not point to a valid MsgNode   
    if(!this->isValid())
    {
        throw std::logic_error("Invalid Message");
    }

    // Otherwise, returns the message of the node
    return this->node_->msg_;
}

// To be completed - must adhere to any requirements in the .h file
// DONE
LabelList::MsgType& LabelList::MsgToken::msg() 
{
    // Throws a logic error if the token does not point to a valid MsgNode   
    if(!this->isValid())
    {
        throw std::logic_error("Invalid Message");
    }
    
    // Otherwise, returns the message of the node
    return this->node_->msg_;
}

// To be completed - must adhere to any requirements in the .h file
// DONE
std::ostream& operator<<(std::ostream& ostr, const LabelList::MsgToken& token)
{
    if(token.isValid())
    {
        ostr << token.node_->msg_;
    }
    return ostr;
}

// Static constant 
const LabelList::MsgToken LabelList::end_(nullptr, nullptr);

// To be completed - must adhere to any requirements in the .h file
// DONE
LabelList::LabelList() 
// Add any initializers here
{
    // Initializes LabelList with the beginnings of the "all" label
    this->labels_.push_back("all");
    this->heads_.push_back(nullptr);
}

// To be completed - must adhere to any requirements in the .h file
// DONE
LabelList::~LabelList()
{
    // Deallocates all nodes
    this->clear();
}

// To be completed - must adhere to any requirements in the .h file
// DONE
void LabelList::clear()
{
    // Forward declaration of nodes to be cleared
    MsgNode* curr_node;
    MsgNode* next_node;

    // Traverse through the "all" list
    curr_node = this->heads_[0];
    while (curr_node != nullptr)
    {
        next_node = curr_node->next_[0];
        // Remove also deallocates the MsgNode
        this->remove(MsgToken(curr_node, this));
        curr_node = next_node;
    }
}

// To be completed - must adhere to any requirements in the .h file
// DONE
bool LabelList::empty() const
{
    return (this->heads_[0] == nullptr);
}

// Complete
size_t LabelList::size() const
{
    MsgNode* n = this->heads_[0];
    size_t cnt = 0;
    while(n != nullptr){
        cnt++;
        n = n->next_[0];
    }
    return cnt;
}

// To be completed - must adhere to any requirements in the .h file
// DONE
LabelList::MsgToken LabelList::add(const MsgType& msg)
{
    // Generate a MsgNode
    MsgNode* node = new MsgNode(msg);

    // Generate a MsgToken        
    MsgToken token = MsgToken(node, this);

    // Label it with 'all'
    label(token, "all");

    return token;
}


// To be completed - must adhere to any requirements in the .h file
// DONE
void LabelList::remove(const MsgToken& token)
{
    // If token is not valid, do nothing
    if(!token.isValid()) return;

    // Unlabel each of the existing labels
    // For each item in labelled_
    int labelled_size = token.node_->labelled_.size();
    for (int i = 0; i < labelled_size; i++)
    {
        // If labelled_ is true
        if (token.node_->labelled_[i] == true)
        {
            // Run unlabel
            token.list_->unlabel(token, token.list_->labels_[i]);
            // This eliminates the pointers and labelled_ bool, 
            // while relinking the rest of the list
        }
    }

    // Special case: Unlabel "all"
    // Get the label index, throw if not
    size_t allIndex = 0;
 
    // Get the previous and next nodes
    MsgNode* prev_node = token.node_->prev_[allIndex];
    MsgNode* next_node = token.node_->next_[allIndex];

    // If there's a previous node, link it to the next node
    if (prev_node != nullptr)
    {
        prev_node->next_[allIndex] = next_node;
    }
    
    // If not, link heads_ to the next node
    else
    {
        token.list_->heads_[allIndex] = next_node;
    }

    // If there's a next node, link it to the previous
    if (token.node_->next_[allIndex] != nullptr)
    {
        next_node->prev_[allIndex] = prev_node;
    }

    // Set your node's labelled_[allIndex] equal to 0
	token.node_->labelled_[allIndex] = 0;

    // Set prev_ and next_ equal to nullptrs
    token.node_->prev_[allIndex] = nullptr;
    token.node_->next_[allIndex] = nullptr;

    // Finally, deallocate memory
    delete token.node_;
}

// --- Insert helper functions here --- 
bool LabelList::checkNodeVecLen(NodeVec v, size_t index)
{
    // Shows whether the vector contains the index
    return index < v.size();
}

bool LabelList::checkBoolVecLen(std::vector<bool> v, size_t index)
{
    // Shows whether the vector contains the index
    return index < v.size();
}

void LabelList::extendNodeVec(NodeVec& v, size_t index, MsgNode* node)
{

    // Adds a node to a NodeVec at the specified index
    // If the NodeVec is too short, adds nullptrs
    while (checkNodeVecLen(v, index) == false)
    {
        v.push_back(nullptr);
    }
    v[index] = node;
}

void LabelList::extendBoolVec(std::vector<bool>& v, size_t index, bool value)
{
    // Adds a node to a BoolVec at the specified index
    // If the BoolVec is too short, adds nullptrs
    while (checkBoolVecLen(v, index) == false)
    {
        v.push_back(false);
    }
    v[index] = value;
}

// Starting from the given token, find the closest previous token with the given label
LabelList::MsgNode* LabelList::findPrevLabelledNode(const MsgToken& token, LabelType label)
{
    // Find some label indexes
    size_t labelIndex = findLabelIndex(label);
    size_t allIndex = findLabelIndex("all");

    // While loop to find the most recent labeled node
    MsgNode* prev_node_all = token.node_->prev_[allIndex];
    MsgNode* prev_node_labelled;
    bool found_prev_node = false;
    while (found_prev_node == false)
    {
        // Is the previous node the head of the list?
        if (prev_node_all == nullptr)
        {
            // Then, there would be no node with your label
            prev_node_labelled = nullptr;
            found_prev_node = true;
        }

        // Could the previous node have your target label?
        else if (checkBoolVecLen(prev_node_all->labelled_, labelIndex))
        {
            // QUESTION: This isn't great style. Really I wanted to run
            // and if with two conditions. But the first condition is
            // to check if the second condition will throw an error, 
            // so I don't want to call the second without knowing that
            // the first is true. How do I write this better?

            // Does it have your target label?
            if (prev_node_all->labelled_[labelIndex] == true)
            {
                // If so, return a pointer to it
                prev_node_labelled = prev_node_all;
                found_prev_node = true;
            }
        }

        // If that node wasn't labelled, go back one more and loop again
        if (found_prev_node == false)
        {
            prev_node_all = prev_node_all->prev_[allIndex];
        }
    }
    return prev_node_labelled;
}

// Starting from the given token, find the next token with the given label
LabelList::MsgNode* LabelList::findNextLabelledNode(const MsgToken& token, LabelType label)
{
    // Find some label indexes
    size_t labelIndex = findLabelIndex(label);
    size_t allIndex = findLabelIndex("all");

    // While loop to find the most recent labeled node
    MsgNode* next_node_all = token.node_->next_[allIndex];
    MsgNode* next_node_labelled;
    bool found_next_node = false;
    while (found_next_node == false)
    {
        // Is the next node the head of the list?
        if (next_node_all == nullptr)
        {
            // Then, there would be no node with your label
            next_node_labelled = nullptr;
            found_next_node = true;
        }

        // Could the next node have your target label?
        else if (checkBoolVecLen(next_node_all->labelled_, labelIndex))
        {
            // Does it have your target label?
            if (next_node_all->labelled_[labelIndex] == true)
            {
                // Bad style, question about this in findPrevLabelledNode 
                // If so, return a pointer to it
                next_node_labelled = next_node_all;
                found_next_node = true;
            }
        }
        // Go to the next node
        if (found_next_node == false)
        {
            next_node_all = next_node_all->next_[allIndex];
        }
    }
    return next_node_labelled;
}

// To be completed - must adhere to any requirements in the .h file
// DONE
void LabelList::label(const MsgToken& token, const LabelType& label)
{
    // Make sure the token has a node
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }

    // Bad style, question about this in findPrevLabelledNode 
    // Basically, the if-else chain got messy, so I created 
    // a condition to tell me if the final if is necessary
    bool final_if = true;

    // Find the index of the label
    size_t labelIndex = findLabelIndex(label);

    // Case #1: Label does not exist
    if (labelIndex == this->INVALID_LABEL) 
    {
        // Add label to this->labels_            
        this->labels_.push_back(label);

        // Get new label index
        size_t newLabelIndex = findLabelIndex(label);
        
        // Add node pointer to this->heads_
        extendNodeVec(this->heads_, newLabelIndex, token.node_);

        // Add True to token.node_->labelled_
        extendBoolVec(token.node_->labelled_, newLabelIndex, true);

        // Add a nullptr to token.node_->prev_
        extendNodeVec(token.node_->prev_, newLabelIndex, nullptr);
        
        // Add nullptr to token->node->next_
        extendNodeVec(token.node_->next_, newLabelIndex, nullptr);

        final_if = false;
    }


    // Case #2: The label already exists, and is "all"
    else if (label == "all")
    {
        // Find the head of the "all" list
        MsgNode* all_node = token.list_->heads_[labelIndex];

        // Case 2.1: "all" exists, and points to a node
        if (all_node != nullptr)
        {
            MsgNode* all_next = all_node->next_[labelIndex];

            // Traverse the list until you find its end
            while (all_next != nullptr &&
                all_next != token.node_)
            {

                all_node = all_next;
                all_next = all_node->next_[labelIndex];

            }

            // Add a pointer from the current end of the "all" list to your node
            all_node->next_[labelIndex] = token.node_;

            // Add a pointer to the end of the "all" list to your node's prev_
            extendNodeVec(token.node_->prev_, labelIndex, all_node);

            // Add a nullptr to your node's next_
            extendNodeVec(token.node_->next_, labelIndex, nullptr);
        }

        // Case 2.2: "all" exists and heads_ points to a nullptr
        else if (all_node == nullptr)
        {
            // Add node pointer to this->heads_
            extendNodeVec(this->heads_, labelIndex, token.node_);

            // Add True to token.node_->labelled_
            extendBoolVec(token.node_->labelled_, labelIndex, true);

            // Add a nullptr to token.node_->prev_
            extendNodeVec(token.node_->prev_, labelIndex, nullptr);
            
            // Add nullptr to token.node->next_
            extendNodeVec(token.node_->next_, labelIndex, nullptr);
        }
        final_if = false;
    }

    // Case #3: The label exists, is not "all", 
    // and the node is already correctly labeled. 
    // Check if labelled_ could contain the label
    else if (checkBoolVecLen(token.node_->labelled_, labelIndex))
    {
        // Bad style, question about this in findPrevLabelledNode 
        // Then, check if labelled_ does contain the label
        if (token.node_->labelled_[labelIndex] == true)
        {
            final_if = false;
            // If it's already labeled, return without changes
        }
    }

    // Case #4: Label already exists, is not "all", and
    // the node has not already been correctly labeled. 
    if (final_if == true)
    {
        // Find pointers to previous and next items in labelled list
        MsgNode* prev_node_label = findPrevLabelledNode(token, label);
        MsgNode* next_node_label = findNextLabelledNode(token, label);

        // If the previous node exists, point from it to this node
        if (prev_node_label != nullptr)
        {
            extendNodeVec(prev_node_label->next_, labelIndex, token.node_);
        }

        // Otherwise, point to this one from heads_
        else 
        {
            extendNodeVec(token.list_->heads_, labelIndex, token.node_);
        }

        // Extend prev_, next_, and labelled_
        extendNodeVec(token.node_->prev_, labelIndex, prev_node_label);
        extendNodeVec(token.node_->next_, labelIndex, next_node_label);
        extendBoolVec(token.node_->labelled_, labelIndex, true);

        // Have the next one point back to this one
        if (next_node_label != nullptr)
        {
            extendNodeVec(next_node_label->prev_, labelIndex, token.node_);
        }
    }
}

// To be completed - must adhere to any requirements in the .h file
// DONE
void LabelList::unlabel(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }

    // If label is "all", do nothing
	if (label == "all") return;

    // Get the label index, throw if not
    size_t labelIndex = this->getLabelIndex(label);

    // If message is not labelled, do nothing
    if (token.node_->labelled_[labelIndex] == 0) return;
 
    // Get the previous and next nodes
    MsgNode* prev_node = token.node_->prev_[labelIndex];
    MsgNode* next_node = token.node_->next_[labelIndex];

    // If there's a previous node, link it to the next node
    if (prev_node != nullptr)
    {
        prev_node->next_[labelIndex] = next_node;
    }
    
    // If not, link heads_ to the next node
    else
    {
        token.list_->heads_[labelIndex] = next_node;
    }

    // If there's a next node, link it to the previous
    if (token.node_->next_[labelIndex] != nullptr)
    {
        next_node->prev_[labelIndex] = prev_node;
    }

    // Set your node's labelled_[labelIndex] equal to 0
	token.node_->labelled_[labelIndex] = 0;

    // Set prev_ and next_ equal to nullptrs
    token.node_->prev_[labelIndex] = nullptr;
    token.node_->next_[labelIndex] = nullptr;
}

// Complete - Do not alter
LabelList::MsgToken LabelList::find(const MsgType& msg, const LabelType& label)
{
    // See if the label exists, will throw if not
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(n != nullptr)
    {
        if(n->msg_ == msg)
        {
            return MsgToken(n, this);
        }
        n = n->next_[level];
    }
    return end();
}

// To be completed - must adhere to any requirements in the .h file
// DONE
LabelList::MsgToken LabelList::find(size_t index, const LabelType& label)
{
    // See if the label exists, will throw if not
    size_t level = this->getLabelIndex(label);
    int index_int = index;
    // New Node is a pointer to the head of that label
    MsgNode* n = this->heads_[level];
    for (int i = 0; i < index_int; i++) 
    {
        if (n->next_[level] != nullptr)
        {
            n = (n->next_[level]);
        }
        else
        {
            return end();
        }
    }
    return MsgToken(n, this);
}

// Complete - Do not alter
LabelList::MsgToken const & LabelList::end() const
{
    return end_;
}

// Complete - Do not alter
void LabelList::print(std::ostream& ostr, const LabelType& label, char separator) const
{
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(nullptr != n)
    {
        ostr << n->msg_ << separator;
        n = n->next_[level];
    }
    ostr << std::endl;
}

// To be completed - must adhere to any requirements in the .h file
// DONE
size_t LabelList::findLabelIndex(const LabelType& label) const
{
    std::vector<LabelType> labels_temp = this-> labels_;
    std::vector<LabelType>::iterator label_iterator;

    label_iterator = std::find(labels_temp.begin(), labels_temp.end(), label);
    
    if (label_iterator == labels_temp.end()) 
    {
        return this->INVALID_LABEL;
    }

    else
    {
        size_t label_index = label_iterator - labels_temp.begin();
        return label_index;
    }
}

// Complete - Do not alter
size_t LabelList::getLabelIndex(const LabelType& label) const
{
    size_t retval = this->findLabelIndex(label);
    if(INVALID_LABEL == retval)
    {
        throw std::out_of_range("Label doesn't exist");
    }
    return retval;
}