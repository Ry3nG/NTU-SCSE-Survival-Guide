#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode
{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;
typedef struct _queuenode
{
    BTNode *node;
    struct _queuenode *next;
} QueueNode;

typedef struct _queue
{
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space, int left);
// Prototypes of Interface functions for Oueue structure
void enqueue(Queue *qPtr, BTNode *node);
int dequeue(Queue *qPtr);
BTNode *getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode *node, int nodev1, int nodeV2);
int dfs(BTNode *root, int target, Queue *path);
void removefromBack(Queue *qPtr);

int main()
{
    BTNode *root = (BTNode *)malloc(sizeof(BTNode));
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;
    BTNode *node;
    enqueue(&q, root);
    int nodeV;
    char opL, opR;
    while (!isEmptyQueue(q))
    {
        scanf("%d %c %c", &nodeV, &opL, &opR);
        node = getFront(q);
        dequeue(&q);
        node->nodeV = nodeV;
        if (opL != '@')
        {
            node->left = (BTNode *)malloc(sizeof(BTNode));
            enqueue(&q, node->left);
        }
        else
            node->left = NULL;
        if (opR != '@')
        {
            node->right = (BTNode *)malloc(sizeof(BTNode));
            enqueue(&q, node->right);
        }
        else
            node->right = NULL;
    }
    int v1, v2;
    scanf("%d %d", &v1, &v2);
    int cost = twoNodesCost(root, v1, v2);

    printBTNode(root, 0, 0);

    printf("Distance is %d\n", cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node)
{
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
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
    { // Queue is empty or NUlL pointer
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
    return q.head->node;
}
int isEmptyQueue(Queue q)
{
    if (q.size == 0)
        return 1;
    else
        return 0;
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
        printf("%d\n", root->nodeV);
        space++;
        printBTNode(root->left, space, 1);
        printBTNode(root->right, space, 0);
    }
}

//--------------------------------
int dfs(BTNode *root, int target, Queue *path)
{
    BTNode *cur = root;
    int result = 0;
    if (cur == NULL)
    {
        return 0;
    }
    enqueue(path, cur);
    if (cur->nodeV == target)
    {
        return 1;
    }

    result = dfs(cur->left, target, path);
    if (result == 1)
    {
        return 1;
    }

    result = dfs(cur->right, target, path);
    if (result == 1)
    {
        return 1;
    }
    else
    {
        removefromBack(path);
        return 0;
    }
}

void removefromBack(Queue *qPtr)
{
    if (qPtr == NULL || qPtr->head == NULL)
    { // Queue is empty or NUlL pointer
        return;
    }
    QueueNode *temp = qPtr->head;
    while (temp->next != qPtr->tail)
    {
        temp = temp->next;
    }
    temp->next = NULL;
    qPtr->tail = temp;
    qPtr->size--;
}

int twoNodesCost(BTNode *node, int nodeV1, int nodeV2)
{
    if (node == NULL)
        return 0;
    Queue path1;
    path1.head = NULL;
    path1.tail = NULL;
    path1.size = 0;

    Queue path2;
    path2.head = NULL;
    path2.tail = NULL;
    path2.size = 0;

    // optain the path from root to nodeV1 and nodeV2
    dfs(node, nodeV1, &path1);
    dfs(node, nodeV2, &path2);

    int lca = 0;
    QueueNode *q1 = path1.head, *q2 = path2.head;

    // find lca
    while (!(isEmptyQueue(path1) || isEmptyQueue(path2)) && q1 != NULL && q2 != NULL)
    {
        if (q1->node->nodeV == q2->node->nodeV)
        {
            lca = q1->node->nodeV;
            q1 = q1->next;
            q2 = q2->next;
        }
        else
        {
            break;
        }
    }

    // calculate result
    int result = 0;
    QueueNode *temp = path1.head;
    while (!isEmptyQueue(path1))
    {
        if (temp->node->nodeV == lca)
        {
            while (temp != NULL)
            {
                result = result + temp->node->nodeV;
                temp = temp->next;
            }
            break;
        }
        temp = temp->next;
    }

    temp = path2.head;
    while (!isEmptyQueue(path2))
    {
        if (temp->node->nodeV == lca)
        {
            while (temp != NULL)
            {
                result = result + temp->node->nodeV;
                temp = temp->next;
            }
            break;
        }
        temp = temp->next;
    }
    result -= lca;
    return result;
}