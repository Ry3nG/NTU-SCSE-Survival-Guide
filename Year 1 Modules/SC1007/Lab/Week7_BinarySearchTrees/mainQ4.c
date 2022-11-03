#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

BTNode *insertBSTNode(BTNode *cur, int item);

void printBTNode(BTNode *root, int space, int left);
BTNode *findBSTNode(BTNode *cur, int item);
void deleteTree(BTNode **root);

void rotateRNode(BTNode **node);

int main()
{
    BTNode *rootBST = NULL;
    BTNode *cur = NULL;
    int item;
    int option;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while (scanf("%d", &item))
    {
        rootBST = insertBSTNode(rootBST, item);
    }
    scanf("%*s");

    printBTNode(rootBST, 0, 0);

    printf("Enter an integer to be searched in the tree:\n");
    scanf("%d", &item);

    cur = findBSTNode(rootBST, item);

    printf("about its left child (0) or right child (1): ");
    scanf("%d", &option);

    if (cur != NULL)
        if (option)
            rotateRNode(&(cur->right));
        else
            rotateRNode(&(cur->left));

    printBTNode(rootBST, 0, 0);

    deleteTree(&rootBST);
    rootBST = NULL;
    return 0;
}

BTNode *insertBSTNode(BTNode *cur, int item)
{
    if (cur == NULL)
    {
        BTNode *node = (BTNode *)malloc(sizeof(BTNode));
        node->item = item;
        node->left = node->right = NULL;
        return node;
    }
    if (item < cur->item)
        cur->left = insertBSTNode(cur->left, item);
    else if (item > cur->item)
        cur->right = insertBSTNode(cur->right, item);
    else
        printf("Duplicated Item: %d\n", item);

    return cur;
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

BTNode *findBSTNode(BTNode *cur, int item)
{
    if (cur == NULL)
    {
        printf("Not Found\n");
        return cur;
    }

    if (item == cur->item)
    {
        printf("Found\n");
        return cur;
    }

    if (item < cur->item)
        return findBSTNode(cur->left, item);
    else
        return findBSTNode(cur->right, item);
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

void rotateRNode(BTNode **node)
{
    if (*(node) == NULL)
        return;

    BTNode *x = (*node)->left;
    BTNode *xRChild;
    if (x != NULL)
        xRChild = x->right;
    else
        return;

    (*node)->left = xRChild;
    x->right = *node;

    (*node) = x;
}
