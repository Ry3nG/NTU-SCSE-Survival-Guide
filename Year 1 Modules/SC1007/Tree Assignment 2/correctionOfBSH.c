#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queueNode
{
    BTNode *data;
    struct _queueNode *next;
} QueueNode;

typedef struct _queue
{
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

typedef struct _stackNode
{
    BTNode *data;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *top;
} Stack;

// Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode *data);
int dequeue(Queue *qPtr);
BTNode *getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode *createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

// Interface funcions for Stack structure
void push(Stack *sPtr, BTNode *data);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

void BSTCorrection(BTNode *root);
void inOrderTraversal(BTNode *root, int *array, int *i);
void walk(BTNode *root, BTNode **a, BTNode **b, int swap0, int swap1);

int main()
{
    BTNode *root = NULL;
    BTNode *temp = NULL;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int item;
    int flag = 1;
    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");

    while (scanf("%d", &item))
    {
        if (root == NULL)
        {
            if (item != -1)
            {
                root = createNode(item);
                enqueue(&q, root);
            }
        }
        else
        {
            while (!isEmptyQueue(q))
            {
                temp = getFront(q);
                if (flag)
                {
                    if (item != -1)
                    {
                        temp->left = createNode(item);
                        enqueue(&q, temp->left);
                    }
                    flag = 0;
                    break;
                }
                else if (temp->right == NULL)
                {
                    if (item != -1)
                    {
                        temp->right = createNode(item);
                        enqueue(&q, temp->right);
                    }
                    dequeue(&q);
                    flag = 1;
                    break;
                }
                else
                    dequeue(&q);
            }
        }
    }
    scanf("%*s");

    printf("The input binary search tree: \n");
    printBTNode(root, 0, 0);
    printf("\n");
    printf("The corrected binary search tree: \n");
    BSTCorrection(root);
    printBTNode(root, 0, 0);
    deleteTree(&root);

    return 0;
}

BTNode *createNode(int item)
{
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    node->item = item;
    node->left = node->right = NULL;
    return node;
}

void printBTNode(BTNode *root, int space, int left)
{
    if (root != NULL)
    {
        int i;
        for (i = 0; i < space - 1; i++)
            printf("|\t");

        if (i < space)
        {
            if (left == 1)
                printf("|---");
            else
                printf("|___");
        }

        printf("%d\n", root->item);

        space++;
        printBTNode(root->left, space, 1);
        printBTNode(root->right, space, 0);
    }
}

void deleteTree(BTNode **root)
{
    if (*root != NULL)
    {
        deleteTree(&((*root)->left));
        deleteTree(&((*root)->right));
        free(*root);
        *root = NULL;
    }
}

void enqueue(Queue *qPtr, BTNode *data)
{
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
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

BTNode *getFront(Queue q)
{
    return q.head->data;
}

int isEmptyQueue(Queue q)
{
    if (q.size == 0)
        return 1;
    else
        return 0;
}

void push(Stack *sPtr, BTNode *data)
{
    StackNode *newNode;
    newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = sPtr->top;
    sPtr->top = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if (sPtr == NULL || sPtr->top == NULL)
    {
        return 0;
    }
    else
    {
        StackNode *temp = sPtr->top;
        sPtr->top = sPtr->top->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

BTNode *peek(Stack s)
{
    return s.top->data;
}

int isEmptyStack(Stack s)
{
    if (s.size == 0)
        return 1;
    else
        return 0;
}

//----------------------------------------------------------------

void BSTCorrection(BTNode *root)
{
    int sorted[100];
    int i = 0;

    inOrderTraversal(root, sorted, &i);
    sorted[i] = -1;

    int correct_sorted[100];
    i = 0;
    while (sorted[i] != -1)
    {
        correct_sorted[i] = sorted[i];
        i++;
    }
    correct_sorted[i] = -1;
    bubbleSort(correct_sorted, i);


    int swap[2];
    i = 0;
    int j = 0;
    while(sorted[i] != -1 || correct_sorted[i] != -1)
    {
        if(sorted[i] != correct_sorted[i])
        {
            swap[j] = sorted[i];
            j++;
        }
        i++;
    }

    BTNode *a, *b;
    walk(root, &a, &b, swap[0], swap[1]);
    a->item = swap[1];
    b->item = swap[0];
}

void inOrderTraversal(BTNode *root, int *array, int *i)
{
    if (root == NULL)
        return;
    inOrderTraversal(root->left, array, i);
    array[*i] = root->item;
    (*i)++;
    inOrderTraversal(root->right, array, i);
}

void walk(BTNode *root, BTNode **a, BTNode **b, int swap0, int swap1)
{
    if (root == NULL)
        return;
    walk(root->left, a, b, swap0, swap1);
    if (root->item == swap0)
        *a = root;
    if (root->item == swap1)
        *b = root;

    walk(root->right, a, b, swap0, swap1);
}
void bubbleSort(int array[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (array[j] > array[j + 1])
                swap(&array[j], &array[j + 1]);
}
void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}