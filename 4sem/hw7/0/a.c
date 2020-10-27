// Iterative C++ program to do merge sort on  
// linked list 
#include <iostream> 
using namespace std; 
  
/* Structure of the Node */
struct Node { 
    int data; 
    struct Node* next; 
}; 
  
  
/* Function to calculate length of linked list */
int length(struct Node* current) 
{ 
    int count = 0; 
    while (current != NULL) { 
        current = current->next; 
        count++; 
    } 
    return count; 
} 
  
/* Merge function of Merge Sort to Merge the two sorted parts 
   of the Linked List. We compare the next value of start1 and  
   current value of start2 and insert start2 after start1 if  
   it's smaller than next value of start1. We do this until 
   start1 or start2 end. If start1 ends, then we assign next  
   of start1 to start2 because start2 may have some elements 
   left out which are greater than the last value of start1.  
   If start2 ends then we assign end2 to end1. This is necessary 
   because we use end2 in another function (mergeSort function)  
   to determine the next start1 (i.e) start1 for next 
   iteration = end2->next */
void merge(struct Node** start1, struct Node** end1,  
          struct Node** start2, struct Node** end2) 
{ 
  
    // Making sure that first node of second 
    // list is higher. 
    struct Node* temp = NULL; 
    if ((*start1)->data > (*start2)->data) { 
        swap(*start1, *start2); 
        swap(*end1, *end2); 
    } 
  
    // Merging remaining nodes 
    struct Node* astart = *start1, *aend = *end1; 
    struct Node* bstart = *start2, *bend = *end2; 
    struct Node* bendnext = (*end2)->next; 
    while (astart != aend && bstart != bendnext) { 
        if (astart->next->data > bstart->data) { 
            temp = bstart->next; 
            bstart->next = astart->next; 
            astart->next = bstart; 
            bstart = temp; 
        } 
        astart = astart->next; 
    } 
    if (astart == aend) 
        astart->next = bstart; 
    else
        *end2 = *end1; 
} 
  
/* MergeSort of Linked List 
   The gap is initially 1. It is incremented as  
   2, 4, 8, .. until it reaches the length of the  
   linked list. For each gap, the linked list is  
   sorted around the gap.  
   The prevend stores the address of the last node after 
   sorting a part of linked list so that it's next node 
   can be assigned after sorting the succeeding list.  
   temp is used to store the next start1 because after  
   sorting, the last node will be different. So it  
   is necessary to store the address of start1 before  
   sorting. We select the start1, end1, start2, end2 for  
   sorting. start1 - end1 may be considered as a list  
   and start2 - end2 may be considered as another list  
   and we are merging these two sorted list in merge  
   function and assigning the starting address to the  
   previous end address. */
void mergeSort(struct Node** head) 
{ 
    if (*head == NULL) 
        return; 
    struct Node* start1 = NULL, *end1 = NULL; 
    struct Node* start2 = NULL, *end2 = NULL; 
    struct Node* prevend = NULL; 
    int len = length(*head); 
  
    for (int gap = 1; gap < len; gap = gap*2) { 
        start1 = *head; 
        while (start1) { 
  
            // If this is first iteration 
            bool isFirstIter = 0; 
            if (start1 == *head) 
                isFirstIter = 1; 
  
            // First part for merging 
            int counter = gap; 
            end1 = start1; 
            while (--counter && end1->next) 
                end1 = end1->next; 
  
            // Second part for merging 
            start2 = end1->next; 
            if (!start2) 
                break; 
            counter = gap; 
            end2 = start2; 
            while (--counter && end2->next) 
                end2 = end2->next; 
  
            // To store for next iteration. 
            Node *temp = end2->next; 
  
            // Merging two parts. 
            merge(&start1, &end1, &start2, &end2); 
  
            // Update head for first iteration, else 
            // append after previous list 
            if (isFirstIter) 
                *head = start1; 
            else
                prevend->next = start1; 
  
            prevend = end2; 
            start1 = temp; 
        } 
        prevend->next = start1; 
    } 
} 
  
  
/* Function to print the Linked List */
void print(struct Node** head) 
{ 
    if ((*head) == NULL) 
        return; 
    struct Node* temp = *head; 
    while (temp != NULL) { 
        printf("%d ", temp->data); 
        temp = temp->next; 
    } 
    printf("\n"); 
} 
  
  
/* Given a reference (pointer to    
   pointer) to the head of a list   
   and an int, push a new node on   
   the front of the list. */
void push(struct Node** head_ref,  
          int new_data)  
{  
    struct Node* new_node = new Node;  
    new_node->data = new_data;  
    new_node->next = (*head_ref);  
    (*head_ref) = new_node;  
}    
  
int main() 
{ 
    // start with empty list  
    struct Node* head = NULL;  
    
    // create linked list  
    // 1->2->3->4->5->6->7  
    push(&head, 7);  
    push(&head, -5);  
    push(&head, 100);  
    push(&head, 4);  
    push(&head, 3);  
    push(&head, 400);  
    push(&head, 1);  
  
    mergeSort(&head); 
  
    print(&head); 
}