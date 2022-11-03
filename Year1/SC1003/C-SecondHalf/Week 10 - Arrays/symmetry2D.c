/*Write the C function that takes in a square two‐dimensional array of integer numbers M
and the array sizes for rows and columns as parameters, and returns 1 if M is symmetric or
0 otherwise. A square two‐dimensional matrix is symmetric iff it is equal to its transpose. It
means that M[i][j] is equal to M[j][i] for 0<=i<=rowSize and 0<=j<=colSize. For example, if
rowSize and colSize are 4, and M is {{1,2,3,4},{2,2,5,6},{3,5,3,7}, {4,6,7,4}}, then M will be
symmetric*/
#include <stdio.h>
#define SIZE 10
#include <stdio.h>
#define SIZE 10
#define INIT_VALUE 999
int symmetry2D(int M[][SIZE], int rowSize, int colSize);
int main()
{
    int M[SIZE][SIZE], i, j, result = INIT_VALUE;
    int rowSize, colSize;

    printf("Enter the array size (rowSize, colSize): \n");
    scanf("%d %d", &rowSize, &colSize);
    printf("Enter the matrix (%dx%d): \n", rowSize, colSize);
    for (i = 0; i < rowSize; i++)
        for (j = 0; j < colSize; j++)
            scanf("%d", &M[i][j]);
    result = symmetry2D(M, rowSize, colSize);
    if (result == 1)
        printf("symmetry2D(): Yes\n");
    else if (result == 0)
        printf("symmetry2D(): No\n");
    else
        printf("Error\n");
    return 0;
}
int symmetry2D(int M[][SIZE], int rowSize, int colSize)
{
    int row, column;
    for (row = 0; row < rowSize; row++)
        for(column = 0; column < colSize; column++)
            if (M[row][column]!=M[column][row])
                return 0;
    return 1;
}