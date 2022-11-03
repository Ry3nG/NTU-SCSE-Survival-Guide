#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 120

typedef struct _btnode
{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode **node, char *preO, char *postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);
BTNode *createNode(char id);
BTNode *constructTreeUntil(char *preO, char *postO, int *preIndex, int low, int high, int size);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s", preO);
    scanf("%s", postO);

    BTNode *root = NULL;
    buildTree(&root, preO, postO);
    if (root == NULL)
        printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}

void inOrder(BTNode *cur)
{
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c", cur->id);
    inOrder(cur->right);
}

void preOrder(BTNode *cur)
{
    if (cur == NULL)
        return;

    printf("%c", cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}

void postOrder(BTNode *cur)
{
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c", cur->id);
}

//----------------------------------------------------------------

BTNode *createNode(char id) // create and return a node with given id
{
    BTNode *temp = (BTNode *)malloc(sizeof(BTNode));

    temp->id = id;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

BTNode *constructTreeUntil(char *preO, char *postO, int *preIndex, int l, int h, int size)
{
    // base case
    if (*preIndex >= size || l > h)
    {
        return NULL;
    }
    BTNode *root = createNode(preO[*preIndex]);
    (*preIndex)++;

    if (l == h)
        return root;

    int i;
    for(i = l; i<=h; i++)
    {
        if((preO[*preIndex]) == postO[i])
            break;
    }
    if (i <= h)
    {
        root->left = constructTreeUntil (preO, postO, preIndex,
                                        l, i, size);
        root->right = constructTreeUntil (preO, postO, preIndex,
                                         i + 1, h-1, size);
    }

    return root;

}
void buildTree(BTNode **node, char *preO, char *postO)
{
    int preIndex = 0;
    int size = strlen(preO);
    *node = constructTreeUntil(preO, postO, &preIndex, 0, size - 1, size);
}
