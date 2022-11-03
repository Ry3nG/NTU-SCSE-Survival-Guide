/*A square matrix (2‐dimensional array of equal dimensions) can be reduced to upper‐
triangular form by setting each diagonal element to the sum of the original elements in
that column and setting to 0s all the elements below the diagonal.*/
#include <stdio.h>
#define SIZE 100

void reduceMatrix2D(int ar[][SIZE], int rowSize, int colSize);

int main()
{
    int rowSize, colSize;
    int row, col;
    int ar[SIZE][SIZE];
    printf("Enter row size and col size:\n");
    scanf("%d %d", &rowSize, &colSize);

    printf("Enter the matrix(%dx%d)\n", rowSize, colSize);
    for (row = 0; row < rowSize; row++)
        for (col = 0; col < colSize; col++)
            scanf("%d", &ar[row][col]);

    reduceMatrix2D(ar, rowSize, colSize);

    printf("The processed matrix is: \n");
    for (row = 0; row < rowSize; row++)
    {
        for (col = 0; col < colSize; col++)
            printf("%d ", ar[row][col]);
        printf("\n");
    }
    return 0;
}

void reduceMatrix2D(int ar[][SIZE], int rowSize, int colSize)
{
    int row, col, i;
    for (row = 0; row < rowSize; row++)
        for (col = 0; col < colSize; col++)
            if (row == col)
                for (i = row + 1; i < rowSize; i++)
                {
                    ar[row][col] += ar[i][col];
                    ar[i][col] = 0;
                }
}