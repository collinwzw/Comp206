/* FILE: linked_lists.c gives an example of a data structure implmented using C Structs
 *
 * The various functions show how to add and print items on a linked list. Main 
 * is the way for user code to use these functions.
 * 
 * Shown in class Feb 20, 2018.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct NODE 
{
        int value;
        struct NODE* next;

} aNode;

void printNodes(aNode* my_node) {

        printf(" %i ", my_node->value);
        if (my_node->next != NULL) {
                printNodes(my_node->next);
        }
}

// We talked about 2 versions of this add function. This was version #1.
aNode* addToLinkedList(aNode* list, int value) {

        aNode* freeSpot;
        aNode* newNode;
        freeSpot = list;

	if( list == NULL ){ // First item added
		newNode = (aNode*)malloc(sizeof(aNode));
		newNode->value = value;
		newNode->next = NULL;
		return newNode;
	}
	
        // Find a free spot at the end to add the value
        while(freeSpot->next != NULL) {
                freeSpot = freeSpot->next;
        }

        newNode = (aNode *)malloc(sizeof(aNode));
        newNode->value = value;
        newNode->next  = NULL;
        freeSpot->next = newNode;

	return list;
}

/* This was version number 2. Only one can be active at a time.
   See if you can uncomment this, make the corresponding change in
  main and get it to work.
void addToLinkedList(aNode** list, int value) {

    aNode *newNode = (aNode *)malloc(sizeof(aNode));
    newNode->value = value;
    newNode->next  = NULL;

    aNode* freeSpot = *list;
    
    if( freeSpot == NULL ) *list = newNode;
    else {
        while(freeSpot->next != NULL) {
            freeSpot = freeSpot->next;
        }
        freeSpot->next = newNode;
    }
}
*/

void printLinkedList(aNode* list) {

        if (list != NULL) {
                printf("Content of list is :");
                printNodes(list);
        } else {
                printf("List is empty.");
        }

        printf("\n");

}

aNode *head=NULL;

int main(void) {
   printLinkedList(head);
   head = addToLinkedList(head, 5);  // This line needs to change if you switch add functions
   head = addToLinkedList(head, 10); // This line needs to change if you swtich add functions
   printLinkedList(head);
}

