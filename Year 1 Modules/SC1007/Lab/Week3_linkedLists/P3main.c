#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;


void printList(ListNode *cur);
ListNode * findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);
void deleteList(ListNode **ptrHead);

int concatenate(ListNode **ptrHead1, ListNode *head2);

int main()
{
    ListNode *head1=NULL;
    ListNode *head2=NULL;
    int size1 =0;
    int size2 =0;
    int item;

    printf("Enter a list of numbers for head1, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        if(insertNode(&head1,size1, item)) size1++;
    scanf("%*s");

    printf("Enter a list of numbers for head2, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        if(insertNode(&head2,size2, item)) size2++;
    scanf("%*s");

    printf("\nBefore concatenate() is called:\n");
    printf("Head 1:\n");
    printList(head1);
    printf("Head 2:\n");
    printList(head2);

    concatenate(&head1,head2);

    printf("\nAfter concatenate() was called:\n");
    printf("Head 1:\n");
    printList(head1);
    printf("Head 2:\n");
    printList(head2);

    if(head1!=NULL)
       deleteList(&head1); //it will remove head2 linked list

    return 0;
}

void printList(ListNode *cur){
    printf("Current List: ");
    while (cur != NULL){
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

ListNode *findNode(ListNode* cur, int index)
{
   if (cur==NULL || index<0)
      return NULL;
   while(index>0){
      cur=cur->next;
      if (cur==NULL)
         return NULL;
      index--;
   }
   return cur;
}

int insertNode(ListNode **ptrHead, int index, int item){
    ListNode  *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = *ptrHead;
        *ptrHead = newNode;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode(*ptrHead, index-1)) != NULL){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        return 1;
    }
    return 0;
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
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