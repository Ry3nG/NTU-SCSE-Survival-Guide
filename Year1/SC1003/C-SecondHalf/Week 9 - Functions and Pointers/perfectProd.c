#include <stdio.h>

int perfectProd1(int num);
void perfectProd2(int num, int *prod);

int main()
{
    int number, result = 0;
    printf("Enter a number: \n");
    scanf("%d", &number);
    printf("Calling perfectProd1() \n");
    printf("perfectProd(1): %d\n", perfectProd1(number));

    printf("Calling perfectProd2() \n");
    perfectProd2(number, &result);
    printf("perfectProd(2): %d\n", result);
}

int perfectProd1(int num)
{
    int result = 1;
    int sum;
    for (int i = 2; i <= num; i++)
    {
        sum = 0;
        for (int j = 1; j < i; j++)
        {
            if (i % j == 0)
            {
                sum = sum + j;
            }
        }
        if (sum == i)
        {
            printf("perfectnumber: %d\n", i);
            result = result * i;
        }
    }
    return result;
}

void perfectProd2(int num, int *prod)
{
    int sum;
    *prod = 1;
    for (int i = 2; i <= num; i++)
    {
        sum = 0;
        for (int j = 1; j < i; j++)
        {
            if (i % j == 0)
            {
                sum = sum + j;
            }
        }
        if (sum == i)
        {
            printf("perfectnumber: %d\n", i);
            *prod = *prod * i;
        }
    }
}