#include <stdio.h>

int allEvenDigits1(int num);
void allEvenDigits2(int num, int *result);

int main()
{
    int number, p = 999, result = 999;

    printf("Enter a number: \n");
    scanf("%d", &number);
    p = allEvenDigits1(number);
    if (p == 1)
        printf("allEvenDigits1(): yes\n");
    else if (p == 0)
        printf("allEvenDigits1(): no\n");
    else
        printf("allEvenDigits1(): error\n");

    allEvenDigits2(number, &result);
    if (result == 1)
        printf("allEvenDigits2(): yes\n");
    else if (result == 0)
        printf("allEvenDigits2(): no\n");
    else
        printf("allEvenDigits2(): error\n");

    return 0;
}

int allEvenDigits1(int number)
{
    do
    {
        if (number % 2 == 1)
        {
            return 0;
        }
        number = number / 10;
    } while (number);

    return 1;
}

void allEvenDigits2(int number, int *result)
{
    *result = 1;
    do
    {
        if (number % 2 == 1)
        {
            *result = 0;
            break;
        }
        number = number / 10;
    } while (number);
}