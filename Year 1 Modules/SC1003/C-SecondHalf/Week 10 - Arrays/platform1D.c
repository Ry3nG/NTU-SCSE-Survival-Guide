/*The number of consecutive array elements in an array that contains the same integer value
forms a ‘platform’. Write a C function platform1D() that takes in an array of integers ar and size
as parameters, and returns the length of the maximum platform in ar to the calling function.*/
#include <stdio.h>
int platform1D(int ar[], int size);
int main()
{
    int i, b[50], size;
    printf("Enter array size: \n");
    scanf("%d", &size);
    printf("Enter %d data: \n", size);
    for (i = 0; i < size; i++)
        scanf("%d", &b[i]);
    printf("platform1D(): %d\n", platform1D(b, size));
    return 0;
}
int platform1D(int ar[], int size)
{
    int length;
    int i, j;
    int count[50];

    length = 0;

    for(i = 0; i < size; i++)
    {
        count[i] = 0;
        for(j = 0; j < size; j++)
        {
            if(ar[j] == ar[i])
            {
                count[i]+=1;
            }
        }
    }

    length = count[0];
    for(i = 0; i < size; i++)
    {
        if (length < count[i])
            length = count[i];
    }

    return length;
}