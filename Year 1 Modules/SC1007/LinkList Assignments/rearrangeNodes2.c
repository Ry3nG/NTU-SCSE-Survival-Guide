#include <stdio.h>
#include <stdlib.h>

struct _listNode
{
    int item;
    struct _listNode *next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList
{
    ListNode *head;
    int size;
} LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList *llptr);

LinkedList rearrange(LinkedList ll);
void appendNode(ListNode *head, int item);

int main()
{
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode *temp;

    int i = 0;

    while (scanf("%d", &i))
    {
        if (ll.head == NULL)
        {
            ll.head = (ListNode *)malloc(sizeof(ListNode));
            temp = ll.head;
        }
        else
        {
            temp->next = (ListNode *)malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = i;
        ll.size++;
    }
    temp->next = NULL;

    ll = rearrange(ll);

    printList(ll);
    deleteList(&ll);
    return 0;
}

void printList(LinkedList ll)
{
    ListNode *temp = ll.head;

    while (temp != NULL)
    {
        printf("%d ", temp->item);
        temp = temp->next;
    }
    printf("\n");
}
void deleteList(LinkedList *llptr)
{
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur != NULL)
    {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    llptr->head = NULL;
    llptr->size = 0;
}

LinkedList rearrange(LinkedList ll)
{
    if(ll.size < 2) return ll;
    ListNode *left = ll.head, *right = NULL;
    ListNode *current = ll.head, *midNode = NULL;
    int count = 0;

    //split the list into left and right
    while (current != NULL)
    {
        if (count == ll.size / 2)
        {
            right = current;
            midNode = current;
            break;
        }
        current = current->next;
        count++;
    }

    current = ll.head;
    while (current->next != midNode)
    {
        current = current->next;
    }
    current->next = NULL;

    ListNode *leftHead = left, *leftNext = left, *leftCur = left;
    ListNode *rightHead = right, *rightNext = right, *rightCur = right;
    while (rightCur != NULL && leftCur != NULL)
    {
        rightNext = rightCur->next;
        rightCur->next = leftCur;
        rightCur = rightNext;
        leftNext = leftCur->next;
        leftCur->next = rightCur;
        leftCur = leftNext;
    }
    ll.head = rightHead;

    left = ll.head, right = NULL;
    current = ll.head, midNode = NULL;
    count = 0;
    //split the list into left and right
    while (current != NULL)
    {
        if (count == ll.size / 2)
        {
            right = current;
            midNode = current;
            break;
        }
        current = current->next;
        count++;
    }
    current = ll.head;
    while (current->next != midNode)
    {
        current = current->next;
    }
    current->next = NULL;

    leftHead = left, leftNext = left, leftCur = left;
    rightHead = right, rightNext = right, rightCur = right;
    while (leftCur != NULL && rightCur != NULL)
    {
        leftNext = leftCur->next;
        leftCur->next = rightCur;
        leftCur = leftNext;
        rightNext = rightCur->next;
        rightCur->next = leftCur;
        rightCur = rightNext;
    }
    ll.head = leftHead;
    if (rightCur != NULL)
        appendNode(ll.head, rightCur->item);

    return ll;
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