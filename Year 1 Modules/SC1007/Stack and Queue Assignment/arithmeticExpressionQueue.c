#include <stdio.h>
#include <stdlib.h>
#include <string.h>\

#define SIZE 1000

enum ExpType
{
    OPT,
    OPERAND
};

typedef struct _queueNode
{
    int item;
    enum ExpType type;
    struct _queueNode *next;
} QueueNode;

typedef struct _queue
{
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

void enqueue(Queue *qptr, int item, enum ExpType type);
int dequeue(Queue *qPtr);
QueueNode *getFront(Queue q);
int isEmptyQueue(Queue q);


void expressionQ(char *infix, Queue *qPtr);
void printExpQ(Queue *qPtr);
int concat(int a, int b);

int main()
{
    char infix[SIZE];
    scanf("%[^\n]%*c", infix);

    Queue inExpQ;
    inExpQ.head = NULL;
    inExpQ.tail = NULL;
    inExpQ.size = 0;
    expressionQ(infix, &inExpQ);
    printf("Output:\n");
    printExpQ(&inExpQ);
    return 0;
}
void enqueue(Queue *qPtr, int item, enum ExpType type)
{
    QueueNode *newNode;
    newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->type = type;
    newNode->next = NULL;
    if (isEmptyQueue(*qPtr))
        qPtr->head = newNode;
    else
        qPtr->tail->next = newNode;
    qPtr->tail = newNode;
    qPtr->size++;
}
int dequeue(Queue *qPtr)
{
    if (qPtr == NULL || qPtr->head == NULL)
        return 0;
    else
    {
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        if (qPtr->head == NULL)
            qPtr->tail = NULL;
        free(temp);
        qPtr->size--;
        return 1;
    }
}
QueueNode *getFront(Queue q)
{
    return q.head;
}
int isEmptyQueue(Queue q)
{
    if (q.size == 0)
        return 1;
    else
        return 0;
}
void printExpQ(Queue *qPtr)
{
    if (qPtr == NULL)
        return;
    QueueNode *temp = NULL;
    temp = getFront(*qPtr);
    while (temp != NULL)
    {
        if (temp->type == OPERAND)
            printf(" %d", temp->item);
        else
            printf("%c", (char)(temp->item));
        dequeue(qPtr);
        temp = getFront(*qPtr);
    }
    printf("\n");
}
//----------------------------------------------------------------
int concat(int a, int b)
{

    char s1[20];
    char s2[20];

    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);

    strcat(s1, s2);

    int c = atoi(s1);

    return c;
}

void expressionQ(char *infix, Queue *qPtr)
{
    Queue stringQueue;
    stringQueue.head = NULL;
    stringQueue.tail = NULL;
    stringQueue.size = 0;

    int i = 0;
    while (infix[i] != '\0')
    {
        if (infix[i] - '0' >= 0 && infix[i] - '0' <= 9)
        {
            enqueue(&stringQueue, infix[i] - '0', OPERAND);
        }
        else
            enqueue(&stringQueue, infix[i], OPT);
        i++;
    }

    int number = 0;
    while(!isEmptyQueue(stringQueue))
    {
        if(getFront(stringQueue)->type == OPERAND)
        {
            number = getFront(stringQueue)->item;
            dequeue(&stringQueue);
            while(!isEmptyQueue(stringQueue) && getFront(stringQueue)->type == OPERAND)
            {
                number = concat(number, getFront(stringQueue)->item);
                dequeue(&stringQueue);
            }
            enqueue(qPtr, number, OPERAND);
        }
        else
        {
            enqueue(qPtr, getFront(stringQueue)->item, OPT);
            dequeue(&stringQueue);
        }
    }
}