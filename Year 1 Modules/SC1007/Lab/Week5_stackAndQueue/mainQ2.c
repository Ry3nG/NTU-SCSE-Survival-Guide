#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    char item;
    struct _listnode *next;
} ListNode;
typedef ListNode StackNode;
typedef ListNode QueueNode;

typedef struct _linkedlist
{
    int size;
    ListNode *head;
} Stack;

typedef struct _queue
{
    int size;
    ListNode *head;
    ListNode *tail;
} Queue;

// Prototypes of Interface functions for Stack structure
void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);
void deleteStack(Stack *sPtr);

// Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, char item);
int dequeue(Queue *qPtr);
char getFront(Queue q);
int isEmptyQueue(Queue q);
void deleteQueue(Queue *qPtr);

int balanced(char *expression);

int main()
{
    char *expression = NULL;
    int i;

    char item;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    printf("Enter an expression, terminated by a newline:\n");
    while (1)
    {
        scanf("%c", &item);
        if (item == '\n')
            break;
        enqueue(&q, item);
    }
    enqueue(&q, '\0');
    expression = (char *)malloc(sizeof(char) * q.size);
    i = 0;
    while (!isEmptyQueue(q))
    {
        expression[i++] = getFront(q);
        dequeue(&q);
    }

    printf("The expression is ");
    printf("%s", balanced(expression) ? "" : "not ");
    printf("balanced.\n");

    if (!expression)
    {
        free(expression);
        expression = NULL;
    }
    return 0;
}

void push(Stack *sPtr, char item)
{
    StackNode *newNode;
    newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if (sPtr == NULL || sPtr->head == NULL)
    {
        return 0;
    }
    else
    {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

char peek(Stack s)
{
    return s.head->item;
}

int isEmptyStack(Stack s)
{
    if (s.size == 0)
        return 1;
    else
        return 0;
}

void deleteStack(Stack *sPtr)
{
    while (pop(sPtr))
        ;
}

void enqueue(Queue *qPtr, char item)
{
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->item = item;
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
    { // Queue is empty or NULL pointer
        return 0;
    }
    else
    {
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        if (qPtr->head == NULL) // Queue is emptied
            qPtr->tail = NULL;

        free(temp);
        qPtr->size--;
        return 1;
    }
}

char getFront(Queue q)
{
    return q.head->item;
}

int isEmptyQueue(Queue q)
{
    if (q.size == 0)
        return 1;
    else
        return 0;
}
void deleteQueue(Queue *qPtr)
{
    while (dequeue(qPtr))
        ;
}

int balanced(char *expression)
{
    // idea: use a stack to store half of the expression
    Stack newStack;
    newStack.head = NULL;
    newStack.size = 0;
    int i = 0;
    while (expression[i] != '\0')
    {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{')
        {
            push(&newStack, expression[i]);
            i++;
        }
        else if (expression[i] == ')')
        {
            if (peek(newStack) == '(')
            {
                pop(&newStack);
                i++;
            }
            else
                return 0;
        }
        else if (expression[i] == ']')
        {
            if (peek(newStack) == '[')
            {
                pop(&newStack);
                i++;
            }
            else
                return 0;
        }
        else if (expression[i] == '}')
        {
            if (peek(newStack) == '{')
            {
                pop(&newStack);
                i++;
            }
            else
                return 0;
        }
        else
            i++;
    }
    return 1;
}
