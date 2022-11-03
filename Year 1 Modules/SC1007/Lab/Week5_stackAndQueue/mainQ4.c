#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 // The limit of expression length

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

void in2Post(char *, char *);
void clearString(char string[]);
void appendString(char string[], char character);
int precedence(char character);

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c", infix);

    in2Post(infix, postfix);
    printf("The postfix expression is \n");
    printf("%s\n", postfix);
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

void in2Post(char *infix, char *postfix)
{
    clearString(postfix);
    int i = 0;
    Stack s;
    s.head = NULL;
    s.size = 0;
    char character;

    while (infix[i] != '\0')
    {
        if (infix[i] == '(')
            push(&s, infix[i]);
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
        {
            character = infix[i];
            if (isEmptyStack(s))
                push(&s, character);
            else
            {
                while (precedence(character) <= precedence(peek(s)))
                {
                    appendString(postfix, peek(s));
                    pop(&s);
                    if (isEmptyStack(s))
                        break;
                }
                push(&s, infix[i]);
            }
        }
        else if (infix[i] == ')')
        {
            character = peek(s);
            while (character != '(')
            {
                appendString(postfix, peek(s));
                pop(&s);
                character = peek(s);
            }
            pop(&s);
        }
        else
            appendString(postfix, infix[i]);
        i++;
    }

    while (!isEmptyStack(s))
    {
        character = peek(s);
        appendString(postfix, character);
        pop(&s);
    }
}

void clearString(char string[])
{
    int i = 0;
    while (i < SIZE)
    {
        string[i] = '\0';
        i++;
    }
}
void appendString(char string[], char character)
{
    int i = 0;
    while (string[i] != '\0')
    {
        i++;
    }
    string[i] = character;
}

int precedence(char character)
{
    switch (character)
    {
    case ('+'):
        return 1;
        break;
    case ('-'):
        return 1;
        break;
    case ('*'):
        return 2;
        break;
    case ('/'):
        return 2;
        break;
    default:
        return 0;
        break;
    }
}