#include <stdio.h>

int sunSqDigits1(int num);
void sunSqDigits2(int num, int *result);

int main()
{
    int num, result;

    printf("Enter a number: \n");
    scanf("%d", &num);
    printf("sumSqDigits1(): %d\n", sunSqDigits1(num));
    sunSqDigits2(num, &result);
    printf("sumSqDigits2(): %d\n", result);
    return 0;
}

int sunSqDigits1(int num)
{
    int numOfDigits=1;
    int count = 0;
    int result=0;
    while (numOfDigits<num)
    {
        numOfDigits = numOfDigits*10;
        count = count + 1;
    }
    for (int i=1; i<=count; i++)
    {
        result = result + (num % 10)*(num % 10);
        num = num/10;
    }
    return result;

}

void sunSqDigits2(int num, int *result)
{
    int numOfDigits=1;
    int count = 0;
    while (numOfDigits<num)
    {
        numOfDigits = numOfDigits*10;
        count = count + 1;
    }
    for (int i=1; i<=count; i++)
    {
        *result = *result + (num % 10)*(num % 10);
        num = num/10;
    }
}