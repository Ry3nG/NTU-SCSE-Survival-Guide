/*Write the C function swapMinMax1D() that takes in an array of integers ar and size (>1) as
parameters, finds the index positions of the largest number and smallest number in the
array, swaps the index positions of these two numbers, and passes the array to the calling
function via call by reference. For example, if ar is {1,2,3,4,5}, then the resultant array ar
will be {5,2,3,4,1} after executing the function. If there are more than one largest or
smallest number in the array, we will swap the last occurrence of the largest and smallest
numbers. For example, if ar is {5,2,1,1,8,9,9}, then the resultant array ar will be
{5,2,1,9,8,9,1} after executing the function*/

#include <stdio.h>
void swapMinMax1D(int ar[], int size);
int main()
{
    int ar[50], i, size;

    printf("Enter array size: \n");
    scanf("%d", &size);
    printf("Enter %d data: \n", size);
    for (i = 0; i < size; i++)
        scanf("%d", ar + i);
    swapMinMax1D(ar, size);
    printf("swapMinMax1D(): ");
    for (i = 0; i < size; i++)
        printf("%d ", *(ar + i));
    return 0;
}
void swapMinMax1D(int ar[], int size)
{
    int max, min, temp;
    int maxIndex = size-1, minIndex = size-1;
    int i;
    max = ar[size-1];
    min = ar[size-1];


    for (i = size-1; i>=0; i--)
    {
        if(ar[i]>max)
        {
            max = ar[i];
            maxIndex = i;
        }
        else if (ar[i]<min)
        {
            min = ar[i];
            minIndex = i;
        }
    }
    ar[maxIndex] = min;
    ar[minIndex] = max;

}
