#include <stdio.h>
int main()
{
    int height = 0;
    int i, j;
    printf("Enter the height: \n");
    scanf("%d", &height);
    printf("Pattern: \n");
    for (i = 1; i <= height; i++)
    {
        for (j = 1; j <= i; j++)
        {
            if (i % 3 == 1)
            {
                printf("1");
            }
            else if (i % 3 == 2)
            {
                printf("2");
            }
            else if (i % 3 == 0)
            {
                printf("3");
            }
            else
            {
                printf("ERROR!");
            }
        }
        printf("\n");
    }

    return 0;
}