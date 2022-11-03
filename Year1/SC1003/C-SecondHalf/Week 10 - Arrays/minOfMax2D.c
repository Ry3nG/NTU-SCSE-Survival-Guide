/*Write a C function minOfMax2D() that takes a two‐dimensional array matrix of integers ar, and
the array sizes for the rows and columns as parameters. The function returns the minimum of
the maximum numbers of each row of the 2‐dimensional array ar. For example, if the rowSize
is 4, colSize is 4, and ar is {{1,3,5,2}, {2,4,6,8}, {8,6,4,9}, {7,4,3,2}}, then the maximum numbers
will be 5, 8, 9 and 7 for rows 0, 1, 2 and 3 respectively, and the minimum of the maximum
numbers will be 5. */
#include <stdio.h>
#define SIZE 10
int minOfMax2D(int ar[][SIZE], int rowSize, int colSize);
int main()
{
    int ar[SIZE][SIZE], rowSize, colSize;
    int i, j, min;

    printf("Enter row size of the 2D array: \n");
    scanf("%d", &rowSize);
    printf("Enter column size of the 2D array: \n");
    scanf("%d", &colSize);
    printf("Enter the matrix (%dx%d): \n", rowSize, colSize);
    for (i = 0; i < rowSize; i++)
        for (j = 0; j < colSize; j++)
            scanf("%d", &ar[i][j]);
    min = minOfMax2D(ar, rowSize, colSize);
    printf("minOfMax2D(): %d\n", min);
    return 0;
}
int minOfMax2D(int ar[][SIZE], int rowSize, int colSize)
{
    int row, col;
    int maxRow, minMax;
    for (row = 0; row < rowSize; row++)
    {
        maxRow = ar[0][0];
        for (col = 0; col < colSize; col++)
            if (maxRow < ar[row][col])
                maxRow = ar[row][col];
        if (row == 0)
            minMax = maxRow;
        else if (minMax > maxRow)
            minMax = maxRow;
    }
    return minMax;
}