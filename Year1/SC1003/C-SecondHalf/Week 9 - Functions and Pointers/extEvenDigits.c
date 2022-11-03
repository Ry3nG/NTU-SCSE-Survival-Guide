#include <stdio.h>
#include <math.h>
#define INIT_VALUE 999
int extEvenDigits1(int num);
void extEvenDigits2(int num, int *result);
int main()
{
    int number, result = INIT_VALUE;

    printf("Enter a number: \n");
    scanf("%d", &number);
    printf("extEvenDigits1(): %d\n", extEvenDigits1(number));
    extEvenDigits2(number, &result);
    printf("extEvenDigits2(): %d\n", result);
    return 0;
}
int extEvenDigits1(int num)
{
    int result = 0;
    int count = 0;
    do
    {
        if (num % 2 == 0)
        {
            result += (num % 10) * (pow(10, count));
            count++;
        }
        else;
        num /= 10;
    } while (num);
    if(count != 0)
    {
        result = result;
    }
    else
    {
        result = -1;
    }
    return result;

}
void extEvenDigits2(int num, int *result)
{
    int count = 0;
    *result = 0;
    do
    {
        if (num % 2 == 0)
        {
            *result += (num % 10) * (pow(10, count));
            count++;
        }
        else;
        num /= 10;
    } while (num);
    if(count != 0)
    {
        *result = *result;
    }
    else
    {
        *result = -1;
    }
}