#include <stdio.h>
int main()
{
    int height;
    int i, j; // iteration count
    char k = '1';
    printf("Enter the height:\n");
    scanf("%d", &height);
    for (i = 1; i <= height; i++)
    {
        k = i + '0';
        printf("%c", k);
        if (k > '9')
            k = '/';
        for (j = 2; j <= i; j++)
        {
            if (k == '9')
                k = '/';
            k = k + 1;
            printf("%c", k);
        }
        printf("\n");
    }
    return 0;
}