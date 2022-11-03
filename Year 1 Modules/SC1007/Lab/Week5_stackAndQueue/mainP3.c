#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;
typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   ListNode *head;
   ListNode *tail;
} Queue;

//simply reuse linked list's print function
void printList(ListNode *cur);

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void deleteQueue(Queue *qPtr);

void recursiveReverse(Queue *qPtr);

int main()
{
    Queue q;
    q.head=NULL;
    q.tail=NULL;
    q.size=0;
    int item;

    printf("Enter a list of numbers for a queue, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        enqueue(&q, item);
    scanf("%*s");

    printf("\nBefore recursiveReverse() is called:\n");
    printList((ListNode *)q.head);

    recursiveReverse(&q);

    printf("\nAfter recursiveReverse() was called:\n");
    printList((ListNode *)q.head);

    deleteQueue(&q);
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

void enqueue(Queue *qPtr, int item){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->item;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}

void deleteQueue(Queue *qPtr)
{
    while(dequeue(qPtr));
}

void recursiveReverse(Queue *qPtr){
//Write your code here




}
