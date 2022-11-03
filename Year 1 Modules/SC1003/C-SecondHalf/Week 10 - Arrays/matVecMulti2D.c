/* Write a C function matVecMult() that accepts a two‐dimensional array M of integer
numbers and a one‐dimensional array V of integer numbers as its parameter values, and
returns the multiplication result of M and V in R via call be reference.*/
#include <stdio.h>
#define SIZE 3
void matVecMult(int M[SIZE][SIZE], int V[SIZE], int R[SIZE]);
int main()
{
    int A[SIZE][SIZE];
    int V[SIZE], R[SIZE];
    int i, j;

    printf("Enter matrix A (%dx%d): \n", SIZE, SIZE);
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            scanf("%d", &A[i][j]);
    printf("Enter matrix V (%dx1): \n", SIZE);
    for (i = 0; i < SIZE; i++)
        scanf("%d", &V[i]);
    printf("matVecMult (AxV): \n");
    matVecMult(A, V, R);
    for (i = 0; i < SIZE; i++)
        printf("%d\n", R[i]);
    printf("\n");
    return 0;
}
void matVecMult(int M[SIZE][SIZE], int V[SIZE], int R[SIZE])
{
    int rowM, columnM;
    int rowV;

    for (rowM = 0; rowM < SIZE; rowM++)
    {
        R[rowM] = 0;
        for (columnM = 0; columnM < SIZE; columnM++)
        {
            rowV = columnM;
            R[rowM] += M[rowM][columnM] * V[rowV];
            rowV+=1;
        }
    }
}
