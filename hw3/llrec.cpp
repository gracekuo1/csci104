#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot){
    if (head == NULL){
        larger = NULL;
        smaller = NULL;
        return;
    }

    Node* this_node = head;
    Node* next_node = head->next;
    if (this_node->val <= pivot){
        smaller = this_node;
        llpivot(next_node, smaller->next, larger, pivot);
    }
    else if (this_node->val > pivot){
        larger = this_node;
        llpivot(next_node, smaller, larger->next, pivot);
    }
    head = NULL;
}
