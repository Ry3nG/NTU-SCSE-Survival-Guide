#include <stdio.h>
int main()
{
    int numLists, numElements, i, j, num, res;
    printf("Enter number of lines: \n");
    scanf("%d", &numLists);
    for (i = 1; i <= numLists; i++)
    {
        printf("Enter line %d: \n", i);
        scanf("%d", &numElements);
        res = 0;
        for (j = 0; j < numElements; j++)
        {
            scanf("%d", &num);
            res = res+num;
        }
        printf("Total: %d\n", res);
    }
    return 0;
}