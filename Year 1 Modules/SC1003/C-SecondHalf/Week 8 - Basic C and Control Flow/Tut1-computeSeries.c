#include <stdio.h>
int fact(int x);
float power(float x, int y);
int main()
{
    float num;
    int i;
    float result, sum= 0;
    printf("Enter x: \n");
    scanf("%f", &num);
    for (i = 1; i <= 10; i++)
    {
        result = (power(num, i) / fact(i));
        sum = sum + result;
    }
    printf("Result = %.2f", sum+1);
    return 0;
}


int fact(int x)
{
    int i;
    int product = 1;
    for (i = 1; i <= x; i++)
    {
        product = product * i;
    }
    return product;
}


float power(float x, int y)
{
    int i;
    float result = 1;
    for (i = 1; i <= y; i++)
    {
        result = result * x;
    }
    return result;
}