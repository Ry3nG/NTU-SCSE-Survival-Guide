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

ListNode *reverseKNodes(ListNode *head, int K);
void reverse(ListNode *head, ListNode *tail);

int main()
{
	ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d", &K);

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

	head = reverseKNodes(head, K);
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

ListNode *reverseKNodes(ListNode *head, int K)
{
	int count = 0;
	ListNode *current  = head, *previous = NULL,*next = NULL, *tempHead = NULL,*tempTail = NULL;
	if(head == NULL || K==1 || K==0 || head->next == NULL) return head;
	while(current != NULL)
	{
		next = current->next;
		count++;
		if (count ==1)
		{
			tempHead = current;
		}
		else if(count == K)
		{
			tempTail = current;
			reverse(tempHead, tempTail);
			if(!previous)
				head = tempTail;
			else
				previous->next = tempTail;

			previous = tempHead;
			count = 0;
		}
		current = next;
	}

	 if (previous != tempHead && tempHead && previous)
        previous->next = tempHead;

	return head;

}

void reverse(ListNode *head, ListNode *tail)
{
	ListNode *current = head, *previous = NULL, *next = NULL;
	while(current != tail)
	{
		next = current->next;
		current ->next = previous;
		previous = current;
		current = next;
	}
	current->next = previous;
}

