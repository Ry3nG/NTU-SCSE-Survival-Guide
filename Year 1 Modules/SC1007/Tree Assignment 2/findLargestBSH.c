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

void enqueue(Queue *qPtr, BTNode *data);
int dequeue(Queue *qPtr);
BTNode *getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode *createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

BTNode *findLargestBST(BTNode *root);
void findBST(BTNode *node, BTNode **result, int *size_ref, int *min_ref, int *max);

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
    printf("The input binary tree: \n");
    printBTNode(root, 0, 0);
    printf("\n");
    BTNode *BSTnode = findLargestBST(root);
    printf("The largest binary search subtree:\n");
    if (BSTnode)
        printBTNode(BSTnode, 0, 0);
    else
        printf("No BST\n");
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

//----------------------------------------------------------------
BTNode *findLargestBST(BTNode *root)
{
    BTNode *result;
    int size = 0;
    int min = INT_MAX;
    int max = INT_MIN;

    findBST(root, &result, &size, &min, &max);
    return result;
}

void findBST(BTNode *node, BTNode **result_ref, int *size_ref, int *min_ref, int *max_ref)
{
    BTNode *result0 = NULL;
    int size0 = 0;
    int min0 = INT_MAX, max0 = INT_MIN;
    if (node->left)
        findBST(node->left, &result0, &size0, &min0, &max0);

    BTNode *result1 = NULL;
    int size1 = 0;
    int min1 = INT_MAX, max1 = INT_MIN;
    if (node->right)
        findBST(node->right, &result1, &size1, &min1, &max1);

    // If both subtrees are BSTs and node value also satisfies, then node is a BST
    if (result0 == node->left && result1 == node->right && (node->left == NULL || max0 <= node->item) && (node->right == NULL || node->item <= min1))
    {
        *result_ref = node;
        *size_ref = size0 + 1 + size1;
        *min_ref = node->left == NULL ? node->item : min0;
        *max_ref = node->right == NULL ? node->item : max1;
    }
    else if (size0 >= size1)
    {
        *result_ref = result0;
        *size_ref = size0;
        *min_ref = min0;
        *max_ref = max0;
    }
    else
    {
        *result_ref = result1;
        *size_ref = size1;
        *min_ref = min1;
        *max_ref = max1;
    }
}