#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int item;
    struct _listnode *next;
} ListNode;

int moveMaxToFront(ListNode **ptrHead);

void printList(ListNode *cur);
ListNode *findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);
void deleteList(ListNode **ptrHead);
void deleteNode(ListNode **head_ref, int position);

int main()
{
    ListNode *head = NULL;
    int size = 0;
    int item;
    int index;

    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while (scanf("%d", &item))
        if (insertNode(&head, size, item))
            size++;
    scanf("%*s");

    printList(head);

    printf("Before moveMaxToFront() is called:\n");
    index = moveMaxToFront(&head);

    printf("After moveMaxToFront() was called:\n");
    printf("The original index of the node with the largest value: %d.\n", index);
    printList(head);

    deleteList(&head);
    return 0;
}

void printList(ListNode *cur)
{
    printf("Current List: ");
    while (cur != NULL)
    {
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

ListNode *findNode(ListNode *cur, int index)
{
    if (cur == NULL || index < 0)
        return NULL;
    while (index > 0)
    {
        cur = cur->next;
        if (cur == NULL)
            return NULL;
        index--;
    }
    return cur;
}

int insertNode(ListNode **ptrHead, int index, int item)
{
    ListNode *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0)
    {
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = *ptrHead;
        *ptrHead = newNode;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode(*ptrHead, index - 1)) != NULL)
    {
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        return 1;
    }
    return 0;
}

void deleteList(ListNode **ptrHead)
{
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur != NULL)
    {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    *ptrHead = NULL;
}

int moveMaxToFront(ListNode **ptrHead)
{
    int index = 0, maxIndex = 0, maxValue = 0;
    ListNode *cur = *ptrHead;
    if(cur == NULL) return -1;
    maxValue = cur->item;
    while(cur != NULL)
    {
        if(cur->item > maxValue)
        {
            maxValue = cur->item;
            maxIndex = index;
        }
        cur = cur->next;
        index+=1;
    }
    deleteNode(ptrHead, maxIndex);
    insertNode(ptrHead, 0,maxValue);
    /*solution idea:
    1.find index of the maxNode using index iteration and maxIndex to store.
    2.extract maxNode content, store to maxValue
    3.use deleteNode() to delete the maxNode from original linkedlist
    4.use insertNode() to insert the new node to the front*/
}

void deleteNode(ListNode **head_ref, int position)
{
    // credit to Geeks for Geeks
    // If linked list is empty
    if (*head_ref == NULL)
        return;

    // Store head node
    ListNode *temp = *head_ref;

    // If head needs to be removed
    if (position == 0)
    {
        *head_ref = temp->next; // Change head
        free(temp);             // free old head
        return;
    }

    // Find previous node of the node to be deleted
    for (int i = 0; temp != NULL && i < position - 1; i++)
        temp = temp->next;

    // If position is more than number of nodes
    if (temp == NULL || temp->next == NULL)
        return;

    // Node temp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    ListNode *next = temp->next->next;

    // Unlink the node from linked list
    free(temp->next); // Free memory

    temp->next = next; // Unlink the deleted node from list
}