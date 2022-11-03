#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 // The limit of expression length

typedef struct _stackNode
{
    double item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, double item);
int pop(Stack *sPtr);
double peek(Stack s);
int isEmptyStack(Stack s);
int isOperand(char c);

double exePostfix(char *);

int main()
{
    char postfix[SIZE];

    printf("Enter a postfix expression:\n");
    scanf("%[^\n]%*c", postfix);

    printf("The answer is %.2lf.\n", exePostfix(postfix));

    return 0;
}

void push(Stack *sPtr, double item)
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

double peek(Stack s)
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

double exePostfix(char *postfix)
{
    Stack newStack;
    newStack.head = NULL;
    newStack.size = 0;
    int i = 0;

    double operand1, operand2;
    while (postfix[i] != '\0')
    {
        if (isOperand(postfix[i]))
        {
            push(&newStack, (postfix[i] - '0'));
            i++;
        }
        else
        {
            operand1 = peek(newStack);
            pop(&newStack);
            operand2 = peek(newStack);
            pop(&newStack);
            switch (postfix[i])
            {
            case '+':
                push(&newStack, operand1 + operand2);
                break;
            case '-':
                push(&newStack, operand2 - operand1);
                break;
            case '*':
                push(&newStack, operand1 * operand2);
                break;
            case '/':
                push(&newStack, operand2 / operand1);
                break;
            }
            i++;
        }
    }
    return peek(newStack);
}

int isOperand(char c)
{
    if (c >= 48 && c <= 57)
        return 1;
    else
        return 0;
}