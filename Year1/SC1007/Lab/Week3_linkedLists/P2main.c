#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int item;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist
{
    ListNode *head;
    int size;
} LinkedList;

void moveEvenItemsToBack(LinkedList *ll);

void printList2(LinkedList ll);
ListNode *findNode2(LinkedList ll, int index);
int insertNode2(LinkedList *ll, int index, int item);
void deleteList2(LinkedList *ptrHead);
void appendNode(ListNode **head_ref, int data);
void deleteNode(ListNode **head_ref, int position);
int concatenate(ListNode **ptrHead1, ListNode *head2);

int main()
{
    LinkedList ll;
    ll.head = NULL;
    ll.size = 0;
    int item;

    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while (scanf("%d", &item))
    {
        if (!insertNode2(&ll, ll.size, item))
            break;
    }

    scanf("%*s");

    printList2(ll);

    moveEvenItemsToBack(&ll);

    printList2(ll);
    deleteList2(&ll);
    return 0;
}

void printList2(LinkedList ll)
{
    ListNode *cur = ll.head;
    printf("Current List has %d elements: ", ll.size);

    while (cur != NULL)
    {
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

ListNode *findNode2(LinkedList ll, int index)
{
    ListNode *cur = ll.head;
    if (cur == NULL || index < 0 || index > ll.size)
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

int insertNode2(LinkedList *ll, int index, int item)
{
    ListNode *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0)
    {
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = ll->head;

        ll->head = newNode;
        ll->size++;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode2(*ll, index - 1)) != NULL)
    {
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        ll->size++;
        return 1;
    }
    return 0;
}

void deleteList2(LinkedList *ll)
{
    ListNode *cur = ll->head;
    ListNode *temp;
    while (cur != NULL)
    {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    ll->head = NULL;
    ll->size = 0;
}

void moveEvenItemsToBack(LinkedList *ll)
{
    ListNode *cur = ll->head;
    LinkedList new_ll;
    new_ll.head = NULL;
    new_ll.size = 0;
    int index = 0, temp = 0;
    while (cur != NULL)
    {
        if (cur->item % 2 == 0)
        {
            temp = cur->item;
            cur = cur->next;
            deleteNode(&ll->head, index);
            index++;
            appendNode(&new_ll.head, temp);
            index--;
        }
        else
        {
            index++;
            cur = cur->next;
        }
    }
    concatenate(&ll->head, new_ll.head);
}

void appendNode(ListNode **head, int new_data)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    ListNode *cur = *head;
    new_node->item = new_data;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    while (cur->next != NULL)
        cur = cur->next;

    cur->next = new_node;
    return;
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
int concatenate(ListNode **ptrHead1, ListNode *head2)
{
    ListNode *cur1 = *ptrHead1, *cur2 = head2;
    if (cur2 == NULL)
        return 0;
    else if (cur1 == NULL)
    {
        cur1->next = head2;
        return 1;
    }
    else
    {
        while(cur1->next != NULL)
        {
            cur1 = cur1->next;
        }
        cur1->next = cur2;
        return 1;
    }
}