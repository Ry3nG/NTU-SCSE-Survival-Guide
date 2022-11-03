#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int item;
    struct _dbllistnode *next;
    struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist
{
    int size;
    CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);
int checkVisible(CDblListNode *start, CDblListNode *end);
int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i, cases;
    int numP;
    scanf("%d", &cases);
    for (i = 0; i < cases; i++)
    {
        while (scanf("%d", &item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n", numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value)
{
    // create a new node
    CDblListNode *newNode;
    newNode = (CDblListNode *)malloc(sizeof(CDblListNode));
    newNode->item = value;
    if (ptrCDLL->size == 0) // first node
    {
        newNode->next = newNode;
        newNode->pre = newNode;
        ptrCDLL->head = newNode;
    }
    else
    {
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; // update last node's next link
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
    }
    ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL)
{
    if (CDLL.head == NULL)
        return;

    CDblListNode *temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head)
    {
        printf("%d ", temp->item);
        temp = temp->next;
    }
    printf("%d\n", temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL)
{
    if (ptrCDLL->head == NULL)
        return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next != ptrCDLL->head)
    {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    free(cur);
    ptrCDLL->head = NULL;
    ptrCDLL->size = 0;
}

int numMountainPairs(CDblLinkedList CDLL)
{
    int count = 0;
    // handle special case
    if (CDLL.size == 0 || CDLL.size == 1)
        return 0;
    else if (CDLL.size == 2)
        return 1;

    // handle complicated case
    CDblListNode *current, *target;
    current = CDLL.head;
    target = current->next->next;
    int flag = 2;

    while(1)
    {
        if (current == CDLL.head)
        {
            flag--;
            if(flag == 0)
            break;
        }
        while (target != current->pre)
        {
            count += checkVisible(current, target);
            target = target->next;
        }
        current = current->next;
        target = current->next->next;
    }
    count = count/2;
    // handle adjacent case
    count += CDLL.size;
    return count;
}
int checkVisible(CDblListNode *start, CDblListNode *end)
{
    // n=0 clock wise, n=1 anti-clockwise
    int minHeight = start->item;
    if (end->item < minHeight)
        minHeight = end->item;
    int flag_cw = 0, flag_acw = 0;
    // clockwise
    CDblListNode *mountainBetween = start->next;
    while (mountainBetween != end)
    {
        if (mountainBetween->item > minHeight)
        {
            flag_cw = 0;
            break;
        }
        else
            mountainBetween = mountainBetween->next;
    }
    if (mountainBetween == end)
        flag_cw = 1;

    mountainBetween = start->pre;
    while (mountainBetween != end)
    {
        if (mountainBetween->item > minHeight)
        {
            flag_acw = 0;
            break;
        }
        else
            mountainBetween = mountainBetween->pre;
    }
    if (mountainBetween == end)
        flag_cw = 1;

    return flag_cw || flag_acw;
}