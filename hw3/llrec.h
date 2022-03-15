#ifndef LLREC_H
#define LLREC_H
#include <cstdlib>
#include <iostream>

/**
 * Node struct for both problems
 */
struct Node
{
    int val;
    Node *next;

    Node(int v, Node* n) : val(v), next(n) {}
};


/**
 * Given a linked list pointed to by head, creates two lists
 * where all values less than or equal to the pivot value are
 * placed in a linked list whose head will be pointed to by
 * smaller and all values greater than the pivot
 * value are placed in a linked list whose head will be pointed to
 * by larger.  The input list pointed to by head should be empty
 * upon return and head set to NULL (i.e. we are not making copies)
 * in the smaller and larger lists but simply moving Nodes out of
 * the input list and into the two other lists.
 * 
 * ==============================================================
 * MUST RUN IN O(n) where n is the number of nodes in the input list
 * ==============================================================
 *
 * @pre: smaller and larger may containing garbage (do NOT have
 *       to be NULL)
 *
 * @param[inout] head
 *   Reference to the head pointer to the input list.
 *   Should be set to NULL upon return
 * @param[out] smaller
 *   Reference to a head pointer for the list of nodes with values
 *   less than or equal to the pivot
 * @param[out] larger
 *   Reference to a head pointer for the list of nodes with values
 *   greater than the pivot
 * @param[in] pivot
 *   Pivot value
 *
 */
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot);

/**
 * Given a linked list pointed to by head, removes (filters out) nodes
 * whose value does not meet the criteria given by the predicate
 * function object, pred (i.e. pred should be a function object that implements
 * `bool operator()(int value)` and returns *true* for items that should
 * be *removed/filtered*.  Removed items should be deallocated.
 *
 * ==============================================================
 * MUST RUN IN O(n) where n is the number of nodes in the input list
 * ==============================================================
 *
 * @param[in] head
 *   Reference to the head pointer to the input list.
 * @param[in] pred
 *   Predicate object implementing: `bool operator()(int value)` that
 *   returns true if a node (based on its value) should be removed.
 * @return a head pointer to the resulting list (since the head pointer
 *   may change [i.e. be filtered])
 *
 */
template <typename Comp>
Node* llfilter(Node* head, Comp pred);

//*****************************************************************************
// Since template implementations should be in a header file, we will
// implement the above function now.
//*****************************************************************************

template <typename Comp>
Node* llfilter(Node* head, Comp pred)
{
    //*********************************************
    // Provide your implementation below
    //*********************************************

    std::cout << "llfilter()" << std::endl;

    // First, we have to find a valid head
    // If the current head is invalid, go to the next one
    while (pred(head->val) == false) {
        Node* temp = head->next;
        delete head;
        head = temp;
        if (head == nullptr) {
            std::cout << "no valid head!" << std::endl;
            break;
        }
    }

    Node* next;
    bool next_true = (head == nullptr);

    // We only filter the rest of the list if the head is valid
    if (head != nullptr) {
        next = head->next;
        next_true = false;
    }

    else {
        next_true = true;
    }

    // Assuming the head is valid, find the next valid node
    // and link it to the current head. 
    // Then recursively call the function again to link the next valid node. 
    while (next_true == false) {
        std::cout << "iterating" << std::endl;
        if (next == nullptr) {
            std::cout << "end of list" << std::endl;
            head->next = nullptr;
            return head;
        }

        if (pred(next->val)) {
            std::cout << "linking!" << std::endl;
            // Then link em up and recurse on next
            head->next = next;
            next_true = true;
            llfilter(next, pred);
        }

        else {
            std::cout << "skipping" << std::endl;
            // Delete the next node, move to its next
            Node* temp = next->next;
            delete next;
            next = temp;
        }
    }

    return head;
}

#endif
