#include <stdio.h>

void minMax(int a[5][5], int *min, int *max);

int main()
{
    int A[5][5];
    int i, j;
    int min, max;

    printf("Enter your matrix data (5x5): \n");
    //nested loop
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            scanf("%d", &A[i][j]);
    minMax(A, &min, &max);
    printf("min = %d; max = %d\n", min, max);
    return 0;
}

void minMax(int array[5][5], int *min, int *max)
{
    /*
    int column, row;
    column = 0;
    row = 0;
    *min = array[row][column];
    *max = array[row][column];
    for (row = 0; row < 5; row++)
    {
        for (column = 0; column < 5; column++)
        {
            if (*min > array[row][column])
                *min = array[row][column];
            else if (*max < array[row][column])
                *max = array[row][column];
        }
    }
    */
    int *ptr;
    ptr = array;
    *min = *ptr;
    *max = *ptr;
    for (int i = 0; i < 25; i++)
    {
        if (*min > *ptr)
            *min = *ptr;
        else if (*max < *ptr)
            *max = *ptr;
        ptr++;
    }
}
