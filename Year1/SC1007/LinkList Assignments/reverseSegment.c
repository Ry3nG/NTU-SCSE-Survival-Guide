#include <stdio.h>
#include <stdlib.h>

struct _listNode
{
    float item;
    struct _listNode *next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode *head, int start, int end);
ListNode *reverse(ListNode *head);
ListNode *findAddress(ListNode *head, int index);

int main()
{
    ListNode *head = NULL, *temp;
    float f = 0.0;
    int S, E;

    scanf("%d %d", &S, &E);

    while (scanf("%f", &f))
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
        temp->item = f;
    }
    temp->next = NULL;

    head = reverseSegment(head, S, E);
    printList(head);
    deleteList(&head);
    return 0;
}

void printList(ListNode *head)
{
    while (head != NULL)
    {
        printf("%.2f ", head->item);
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

ListNode *reverseSegment(ListNode *head, int start, int end)
{
    // when start = end
    if (start == end)
        return head;
    else if (start > end)
        return head;

    ListNode *beforeStart = NULL, *afterEnd = NULL, *startAddress = NULL, *endAddress = NULL;
    int i = 1;

    beforeStart = findAddress(head, start - 1);
    afterEnd = findAddress(head, end + 1);
    startAddress = findAddress(head, start);
    endAddress = findAddress(head, end);

    if (endAddress == NULL || startAddress == NULL)
        return head;
    //unlink endAddress and the remainder
    endAddress->next = NULL;

    //reversing the segment
    endAddress = reverse(startAddress);

    //connect head to reversed segment
    if (beforeStart != NULL)
        beforeStart->next = endAddress;
    else
        head = endAddress;

    //linked back the reversed part and the remainder
    startAddress->next = afterEnd;

    return head;
}

ListNode *reverse(ListNode *head)
{
    ListNode *current = head, *previous = NULL, *next = NULL;

    while (current)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}

ListNode *findAddress(ListNode *head, int index)
{
    ListNode *cur = head;
    int i = 0;
    if (index < 0)
        return NULL;
    if (index == 0)
        return head;
    while (cur != NULL)
    {
        if (i++ < index)
        {
            cur = cur->next;
        }
        else
        {
            return cur;
        }
    }
    return NULL;
}