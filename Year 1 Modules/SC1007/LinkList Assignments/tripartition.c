#include <stdio.h>
#include <stdlib.h>

struct _listNode
{
    int item;
    struct _listNode *next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode **head, int pivot);
void appendNode(ListNode *head, int item);
int main()
{
    ListNode *head = NULL, *temp;
    int i = 0;
    int pivot = 0;

    scanf("%d", &pivot);

    while (scanf("%d", &i))
    {
        if (head == NULL)
        {
            head = (ListNode *)malloc(sizeof(ListNode));
            temp = head;
        }
        else
        {
            temp->next = (ListNode *)malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = i;
    }
    temp->next = NULL;

    triPartition(&head, pivot);
    printList(head);
    deleteList(&head);

    return 0;
}

void printList(ListNode *head)
{
    while (head != NULL)
    {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
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

void triPartition(ListNode **head, int pivot)
{
    ListNode *headPivot = NULL, *midPivot = NULL, *tailPivot = NULL;
    ListNode *headFlag = NULL, *midFlag = NULL, *tailFlag = NULL;
    headPivot = (ListNode *)malloc(sizeof(ListNode));
    midPivot = (ListNode *)malloc(sizeof(ListNode));
    tailPivot = (ListNode *)malloc(sizeof(ListNode));

    ListNode *current = *head, *temp = NULL;

    // locating the 3 pivots
    current = *head;
    while (current != NULL)
    {
        if (current->item == pivot)
        {
            midFlag = current;
            midPivot->item = current->item;
            midPivot->next = NULL;
            break;
        }
        current = current->next;
    }
    if (current == NULL)
        midPivot = NULL;

    current = *head;
    while (current != NULL)
    {
        if (current->item > pivot)
        {
            tailFlag = current;
            tailPivot->item = current->item;
            tailPivot->next = NULL;
            break;
        }
        current = current->next;
    }
    if (current == NULL)
        tailPivot = NULL;

    current = *head;
    while (current != NULL)
    {
        if (current->item < pivot)
        {
            headFlag = current;
            headPivot->item = current->item;
            headPivot->next = NULL;
            break;
        }
        current = current->next;
    }
    if (current == NULL)
        headPivot = NULL;

    //appending respective lists
    current = *head;
    while (current != NULL)
    {
        if (current->item < pivot && current != headFlag)
            appendNode(headPivot, current->item);
        else if (current->item == pivot && current != midFlag)
            appendNode(midPivot, current->item);
        else if (current->item > pivot && current != tailFlag)
            appendNode(tailPivot, current->item);
        current = current->next;
    }

    //linked back the whole list
    if (headPivot != NULL)
    {
        *head = headPivot;
        current = midPivot;
        while (current != NULL)
        {
            appendNode(headPivot, current->item);
            current = current->next;
        }
        current = tailPivot;
        while (current != NULL)
        {
            appendNode(headPivot, current->item);
            current = current->next;
        }
    }
    else
    {
        *head = midPivot;
        current = tailPivot;
        while (current != NULL)
        {
            appendNode(midPivot, current->item);
            current = current->next;
        }
    }
}

void appendNode(ListNode *head, int item)
{
    ListNode *last = head;
    while (last->next != NULL)
        last = last->next;
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->item = item;
    newNode->next = NULL;
    last->next = newNode;
}