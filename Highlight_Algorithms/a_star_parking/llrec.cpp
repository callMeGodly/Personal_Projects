#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

// llpivot will recurse through a singly linked list separating each nodes value
// in comparison to the pivot into two singly linked lists called smaller and larger
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
    
    // terminating case when the pointer equals to NULL, the list is at the end
    if(head == NULL){
        
        // ensures that the end of the lists don't wrap to its previous next
        larger = NULL;
        smaller = NULL;
        head = NULL;
        return; // ends recursion
    }
    else{
            
        // if the value is larger than the pivot it gets added to the larger list
        if(head->val > pivot){
            larger = head;
            head = head->next; // so that the head at the end will point to NULL and be empty
            llpivot(head, smaller, larger->next, pivot);
        }
        // else the value is smaller or equal to the pivot gets added to the smaller list
        else{
            smaller = head;
            head = head->next; // so that the head at the end will point to NULL and be empty
            llpivot(head, smaller->next, larger, pivot);
        }
    }
}
