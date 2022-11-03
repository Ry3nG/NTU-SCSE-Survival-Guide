/* Write a function that takes a square matrix ar, and the array sizes for the rows and
columns as parameters, and returns the transpose of the array via call by reference. For
example, if the rowSize is 4, colSize is 4, and the array ar is {1,2,3,4, 5,1,2,2, 6,3,4,4,
7,5,6,7}, then the resultant array will be {1,5,6,7, 2,1,3,5, 3,2,4,6, 4,2,4,7}. */
#include <stdio.h>
#define SIZE 100

void transpose2D(int ar[][SIZE], int rowSize, int colSize);

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

    transpose2D(ar, rowSize, colSize);

    for(row = 0; row < rowSize; row++)
    {
        for(col = 0; col < colSize; col++)
            printf("%d ", ar[row][col]);
        printf("\n");
    }

    return 0;
}

void transpose2D(int ar[][SIZE], int rowSize, int colSize)
{
    int row, col;
    int temp[SIZE][SIZE];
    for(col = 0; col < colSize; col++)
    {
        for(row = 0; row < rowSize; row++)
        {
           temp[col][row] = ar[row][col];
        }
    }
    for(row = 0; row < rowSize; row++)
    {
        for(col = 0; col < colSize; col++)
            ar[row][col] = temp[row][col];
    }
}
