/*
Write a C function that takes in an one‐dimensional array of integers ar and size as parameters.
The function finds the minimum and maximum numbers of the array. The function returns the
minimum and maximum numbers through the pointer parameters min and max via call by
reference.*/
#include <stdio.h>

void findMinMax1D(int ar[], int size, int *min, int *max);

int main()
{
    int ar[40];
    int i, size;
    int min, max;
    printf("Enter array size: \n");
    scanf("%d", &size);
    printf("Enter %d data: \n", size);
    for (i = 0; i < size; i++)
        scanf("%d", &ar[i]);
    findMinMax1D(ar, size, &min, &max);
    printf("min = %d; max = %d\n", min, max);
    return 0;
}

void findMinMax1D(int ar[], int size, int *min, int *max)
{
    int *ptr;
    ptr = ar;
    *max = *ptr;
    *min = *ptr;
    for (int i = 0; i < size; i++)
    {
        if (*ptr > *max)
        {
            *max = *ptr;
        }
        if (*ptr < *min)
        {
            *min = *ptr;
        }
        ptr++;
    }
}