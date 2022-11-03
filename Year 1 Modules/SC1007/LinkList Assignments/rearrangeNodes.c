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
    ListNode *left = NULL, *right = NULL;
    left = (ListNode *)malloc(sizeof(ListNode));
    right = (ListNode *)malloc(sizeof(ListNode));

    int count = 0;
    ListNode *current = ll.head, *midNode = NULL;

    //initialize left list head
    left->item = ll.head->item;
    left->next = NULL;
    //initialize right list head
    while (current != NULL)
    {
        if (count == ll.size / 2)
        {
            right->item = current->item;
            right->next = NULL;
            midNode = current;
            break;
        }
        current = current->next;
        count++;
    }
    //initialize left list
    current = ll.head->next;
    while (current != midNode)
    {
        appendNode(left, current->item);
        current = current->next;
    }
    //initialize right list
    current = midNode->next;
    while (current != NULL)
    {
        appendNode(right, current->item);
        current = current->next;
    }

    //forming first arranged list
    ListNode *arrange = NULL;
    arrange = (ListNode *)malloc(sizeof(ListNode));
    arrange->item = right->item;
    arrange->next = NULL;
    right = right->next;

    count = 1;
    while (count < ll.size)
    {
        if (count % 2 != 0 && left != NULL) //append left
        {
            appendNode(arrange, left->item);
            left = left->next;
        }
        else if (count % 2 == 0 && right != NULL) //append right
        {
            appendNode(arrange, right->item);
            right = right->next;
        }
        else
            printf("Unexpected Error!\n");
        count++;
    }

    ll.head = arrange;

    count = 0;
    current = ll.head, midNode = NULL;
    left = (ListNode *)malloc(sizeof(ListNode));
    right = (ListNode *)malloc(sizeof(ListNode));
    //initialize left list head
    left->item = ll.head->item;
    left->next = NULL;
    //initialize right list head
    while (current != NULL)
    {
        if (count == ll.size / 2)
        {
            right->item = current->item;
            right->next = NULL;
            midNode = current;
            break;
        }
        current = current->next;
        count++;
    }
    //initialize left list
    current = ll.head->next;
    while (current != midNode)
    {
        appendNode(left, current->item);
        current = current->next;
    }
    //initialize right list
    current = midNode->next;
    while (current != NULL)
    {
        appendNode(right, current->item);
        current = current->next;
    }

    //forming second arranged list
    arrange->item = left->item;
    arrange->next = NULL;
    left = left->next;

    count = 1;
    while (count < ll.size)
    {
        if (count % 2 != 0 && right != NULL) //append right
        {
            appendNode(arrange, right->item);
           right = right->next;
        }
        else if (count % 2 == 0 && left != NULL) //append left
        {
            appendNode(arrange, left->item);
            left = left->next;
        }
        else
            appendNode(arrange, right->item);
        count++;
    }

    ll.head = arrange;
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