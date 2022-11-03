#include <stdio.h>
int main()
{
    int height;
    int i, j; // iteration counter
    char k;   // character
    printf("Enter the height:\n");
    scanf("%d", &height);
    for (i = 1; i <= height; i++)
    {
        if (i % 2 == 1)
            k = 'A';
        else
            k = 'B';
        printf("%c", k);
        for (j = 2; j <= i; j++)
        {
            if (i % 2 == 1)
            {
                if (j % 2 == 1)
                    k = 'A';
                else
                    k = 'B';
            }
            else
            {
                if (j % 2 == 1)
                    k = 'B';
                else
                    k = 'A';
            }
            printf("%c", k);
        }
        printf("\n");
    }
    return 0;
}