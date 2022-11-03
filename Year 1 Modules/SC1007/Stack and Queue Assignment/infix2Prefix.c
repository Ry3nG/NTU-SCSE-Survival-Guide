#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000 // The size of the array
enum ExpType
{
    OPT,
    OPERAND
};

typedef struct _stackNode
{
    char item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int item;
    enum ExpType type;
    struct _listnode *next;
} ListNode;

typedef struct _linkedList
{
    int size;
    ListNode *head;
} LinkedList;

void insertNode(LinkedList *llptr, int item, enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llptr);
int isEmptyLinkedList(LinkedList ll);

void in2PreLL(char *infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);
int precedence(char c);
void appendNode(LinkedList *LLPtr, int item, enum ExpType type);
void reverse(LinkedList *LLPtr);

int main()
{
    char infix[SIZE];
    // printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c", infix);

    LinkedList inExpLL;

    inExpLL.head = NULL;
    inExpLL.size = 0;
    in2PreLL(infix, &inExpLL);
    printExpLL(inExpLL);
    removeAllNodes(&inExpLL);
    return 0;
}
void printExpLL(LinkedList inExpLL)
{
    ListNode *temp = NULL;
    temp = inExpLL.head;
    while (temp != NULL)
    {
        if (temp->type == OPERAND)
            printf(" %d ", temp->item);
        else
            printf("%c", (char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}
void insertNode(LinkedList *LLPtr, int item, enum ExpType type)
{
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if (newNode == NULL)
        exit(0);
    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head = newNode;
    LLPtr->size++;
}
int deleteNode(LinkedList *LLPtr)
{
    if (LLPtr == NULL || LLPtr->size == 0)
    {
        return 0;
    }
    else
    {
        ListNode *temp = LLPtr->head;
        LLPtr->head = LLPtr->head->next;

        free(temp);
        LLPtr->size--;
        return 1;
    }
}
int isEmptyLinkedList(LinkedList ll)
{
    if (ll.size == 0)
        return 1;
    else
        return 0;
}
void removeAllNodes(LinkedList *LLPtr)
{
    while (deleteNode(LLPtr))
        ;
}

void push(Stack *sPtr, char item)
{
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
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

//----------------------------------------------------------------
void appendNode(LinkedList *LLPtr, int item, enum ExpType type)
{
    if (LLPtr->head == NULL)
    {
        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
        if (newNode == NULL)
            exit(0);
        newNode->item = item;
        newNode->type = type;
        newNode->next = NULL;
        LLPtr->head = newNode;
        LLPtr->size++;
        return;
    }
    ListNode *last = LLPtr->head;
    while (last->next != NULL)
        last = last->next;
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL)
        exit(0);
    newNode->item = item;
    newNode->type = type;
    newNode->next = NULL;
    last->next = newNode;
    LLPtr->size++;
}

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

int precedence(char c)
{
    switch (c)
    {
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case '*':
        return 2;
        break;
    case '/':
        return 2;
        break;
    case '%':
        return 2;
        break;
    default:
        printf("Unexpected operator!\n");
        break;
    }
}

void reverse(LinkedList *LLPtr)
{
    ListNode *current = LLPtr->head, *previous = NULL, *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    LLPtr->head = previous;
    current = LLPtr->head;
    while (current != NULL)
    {
        if (current->item == '(')
            current->item = ')';
        else if (current->item == ')')
            current->item = '(';

        current = current->next;
    }
}

void in2PreLL(char *infix, LinkedList *inExpLL)
{

    // step 1: convert the string into a LinkedList and combine the digits
    int i = 0;
    while (infix[i] != '\0')
    {
        if (infix[i] >= '0' && infix[i] <= '9')
            appendNode(inExpLL, infix[i] - '0', OPERAND);
        else
            appendNode(inExpLL, infix[i], OPT);
        i++;
    }

    ListNode *current = inExpLL->head, *next = NULL;
    while (current != NULL)
    {
        if (current->item >= 0 && current->item <= 9)
        {
            next = current->next;
            while (next != NULL && next->item >= 0 && next->item <= 9)
            {
                current->item = concat(current->item, next->item);
                inExpLL->size--;
                next = next->next;
            }
            current->next = next;
        }
        current = current->next;
    }
    // step 2: reverse the list
    reverse(inExpLL);

    // step 3: convert infix to postfix
    LinkedList poExpLL;
    poExpLL.head = NULL;
    poExpLL.size = 0;
    current = inExpLL->head;

    Stack S;
    S.head = NULL;
    S.size = 0;

    while (current != NULL)
    {
        if (current->type == OPERAND)
        {
            appendNode(&poExpLL, current->item, OPERAND);
        }
        else if (current->item == ')')
        {
            while (peek(S) != '(')
            {
                appendNode(&poExpLL, peek(S), OPT);
                pop(&S);
            }
            pop(&S);
        }
        else if (current->item == '(')
        {
            push(&S, current->item);
        }
        else
        {
            while (!isEmptyStack(S) && peek(S) != '(' && precedence(peek(S)) > precedence(current->item))
            {
                appendNode(&poExpLL, peek(S), OPT);
                pop(&S);
            }
            push(&S, current->item);
        }
        current = current->next;
    }
    while (!isEmptyStack(S))
    {
        appendNode(&poExpLL, peek(S), OPT);
        pop(&S);
    }

    // step 4: reverse the postfix list
    removeAllNodes(inExpLL);
    inExpLL->head = poExpLL.head;
    inExpLL->size = poExpLL.size;
    reverse(inExpLL);
}
