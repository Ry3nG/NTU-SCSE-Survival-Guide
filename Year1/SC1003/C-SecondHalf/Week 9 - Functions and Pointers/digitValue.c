#include <stdio.h>

int digitValue1(int num, int k);
void digitValue2(int num, int k, int *result);

int main()
{
    while (1)
    {
        int num, digit, result = -1;

        printf("Enter the number: \n");
        scanf("%d", &num);
        printf("Enter k position: \n");
        scanf("%d", &digit);
        printf("digitValue(1): %d\n", digitValue1(num, digit));
        digitValue2(num, digit, &result);
        printf("digitValue(2): %d\n", result);
    }
    return 0;
}

int digitValue1(int num, int k)
{
    int result = 0, divider = 1;
    for (int i = 1; i <= k; i++)
    {
        divider = divider * 10;
    }
    result = num / (divider / 10) - (num / divider) * 10;
    return result;
}

void digitValue2(int num, int k, int *result)
{
    int divider = 1;
    for (int i = 1; i <= k; i++)
    {
        divider = divider * 10;
    }
    *result = num / (divider / 10) - (num / divider) * 10;
}