# include <stdio.h>
# include <math.h>
float absoluteSum1D(int size, float vector[]);

int main(){
    float vector[10];
    int i, size;

    printf("Enter vector size: \n");
    scanf("%d",&size);
    printf("Enter %d data: \n", size);
    for (i=0; i<size; i++)
        scanf("%f",&vector[i]);
    printf("AbsoluteSum1D(): %.2f\n", absoluteSum1D(size, vector));
    return 0;
}
float absoluteSum1D(int size, float vector[])
{
    float *ptr;
    int i;
    ptr = vector;
    float sum =  0.0;
    for (i=0; i<size; i++)
    {
        sum += abs(*ptr);
        ptr++;
    }
    return sum;
}