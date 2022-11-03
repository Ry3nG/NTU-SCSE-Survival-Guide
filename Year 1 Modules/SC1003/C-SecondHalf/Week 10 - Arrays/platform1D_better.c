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

    int i = 0, max = 0, p;
    while (i < size)
    {
        p = 1;
        i++;
        while (i < size && ar[i - 1] == ar[i])
        {
            p++;
            i++;
        }
        if (p > max)
            max = p;
    }
    return max;
}