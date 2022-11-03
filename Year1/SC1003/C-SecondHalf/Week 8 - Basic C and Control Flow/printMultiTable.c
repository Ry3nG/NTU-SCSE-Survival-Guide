#include <stdio.h>

int main()
{
    int num;
    int i = 1, j = 1;
    printf("Enter a number (between 1 and 9)\n");
    scanf("%d", &num);
    printf("Multiplication table: \n");
    printf(" ");
    for (i = 1; i <= num; i++)
    {
        printf(" %d", i);
    }
    printf("\n");
    for (i = 1; i <= num; i++)
    {
        printf("%d", i);
        for (j = 1; j <= num; j++)
        {
            if (j <= i)
            {
                printf(" %d", j * i);
            }
        }
        printf("\n");
    }
    return 0;
}