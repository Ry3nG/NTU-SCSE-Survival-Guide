/*Write a C function that accepts a two‐dimensional array of integers ar, and the array
sizes for the rows and columns as parameters, computes the sum of the elements of the
two diagonals, and returns the sums to the calling function through the pointer
parameters, sum1 and sum2, using call by reference. For example, if the rowSize is 3,
colSize is 3, and the array ar is {1,2,3, 1,1,1, 4,3,2}, then sum1 is computed as 1+1+2=4,
and sum2 is 3+1+4=8.*/
#include <stdio.h>
#define SIZE 10
void diagonals2D(int ar[][SIZE], int rowSize, int colSize, int *sum1, int *sum2);
int main()
{
    int ar[SIZE][SIZE], rowSize, colSize;
    int i, j, sum1 = 0, sum2 = 0;

    printf("Enter row size of the 2D array: \n");
    scanf("%d", &rowSize);
    printf("Enter column size of the 2D array: \n");
    scanf("%d", &colSize);
    printf("Enter the matrix (%dx%d): \n", rowSize, colSize);
    for (i = 0; i < rowSize; i++)
        for (j = 0; j < colSize; j++)
            scanf("%d", &ar[i][j]);
    diagonals2D(ar, rowSize, colSize, &sum1, &sum2);
    printf("sum1=%d; sum2=%d\n", sum1, sum2);
}
void diagonals2D(int ar[][SIZE], int rowSize, int colSize, int *sum1, int *sum2)
{
    int row, column;
    *sum1 = 0;
    *sum2 = 0;
    for (row = 0; row < rowSize; row++)
        for (column = 0; column < colSize; column++)
        {
            if (row == column)
                *sum1 += ar[row][column];
            if (row + column == colSize-1)
                *sum2 += ar[row][column];
        }
}