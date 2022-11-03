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

// Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode *data);
int dequeue(Queue *qPtr);
BTNode *getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode *insertBTNode(BTNode *cur, int item);
void removeAll(BTNode **node);
void printBTNode(BTNode *root, int space, int left);

void levelOrder(BTNode *root);

int main()
{
    BTNode *root = NULL;
    int item;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while (scanf("%d", &item))
        root = insertBTNode(root, item);
    scanf("%*s");

    printBTNode(root, 0, 0);
    levelOrder(root);

    removeAll(&root);

    return 0;
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

BTNode *insertBTNode(BTNode *cur, int item)
{
    if (cur == NULL)
    {
        BTNode *node = (BTNode *)malloc(sizeof(BTNode));
        node->item = item;
        node->left = node->right = NULL;
        return node;
    }
    if (rand() % 2)
        cur->left = insertBTNode(cur->left, item);
    else
        cur->right = insertBTNode(cur->right, item);

    return cur;
}

void removeAll(BTNode **node)
{
    if (*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
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

void levelOrder(BTNode *root)
{
    Queue Q;
    BTNode *temp = NULL;
    enqueue(&Q, root);
    while (!isEmptyQueue(Q))
    {
        temp = getFront(Q);
        dequeue(&Q);
        printf("%d\n", temp->item);

        if (temp->left!=NULL)
            enqueue(&Q, temp->left);
        if (temp->right!= NULL)
            enqueue(&Q, temp->right);
    }
}
