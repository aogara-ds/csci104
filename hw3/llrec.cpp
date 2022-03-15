#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) 
{
    std::cout << "llpivot()" << std::endl;

    if (head == nullptr) {
        std::cout << "head is null" << std::endl;
        return;
    }
    
    Node* next_head = head->next;

    if (head->val <= pivot) {
        std::cout << "smaller!" << std::endl;
        smaller = head;
        smaller->next = nullptr;

        llpivot(next_head, smaller->next, larger, pivot);
    }

    else {
        std::cout << "larger!" << std::endl;
        larger = head;
        larger->next = nullptr;

        llpivot(next_head, smaller, larger->next, pivot);
    }

    head = nullptr;

}

