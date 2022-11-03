#include <stdio.h>
#include <math.h>
int reverseDigits1(int num);
void reverseDigits2(int num, int *result);

int main()
{
    int num, result = 999;

    printf("Enter a number: \n");
    scanf("%d", &num);
    printf("reverseDigits1(): %d\n", reverseDigits1(num));
    reverseDigits2(num, &result);
    printf("reverseDigits2(): %d\n", result);
    return 0;
}
int reverseDigits1(int num)
{
    int digit = 0;
    int result = 0;
    do
    {
        digit = num % 10;
        result = result * 10 + digit;
        num /= 10;
    } while (num);
    return result;
}

void reverseDigits2(int num, int *result)
{
    int digit = 0;
    *result = 0;
    do
    {
        digit = num % 10;
        *result = *result * 10 + digit;
        num /= 10;
    } while (num);
}