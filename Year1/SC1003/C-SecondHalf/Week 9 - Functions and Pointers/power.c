#include <stdio.h>

float power1(float num, int p);
void power2(float num, int p, float *result);

int main()
{
    while (1)
    {
        int power;
        float number, result = 1;

        printf("Enter the number and power: \n");
        scanf("%f %d", &number, &power);
        printf("power(1): %.2f\n", power1(number, power));
        power2(number, power, &result);
        printf("power(2): %.2f\n", result);
    }
    return 0;
}

float power1(float num, int power)
{
    float result = 1;
    if (power > 0)
    {

        for (int i = 0; i < power; i++)
        {
            result = result * num;
        }
        return result;
    }
    else if (power == 0)
    {
        return result;
    }
    else
    {
        power = -power;
        for (int i = 0; i < power; i++)
        {
            result = result * num;
        }
        return 1 / result;
    }
}

void power2(float num, int power, float *result)
{
    if (power > 0)
    {
        for (int i = 0; i < power; i++)
        {
            *result = *result * num;
        }
    }
    else if (power == 0)
    {
        *result = 1;
    }
    else
    {
        power = -power;
        for (int i = 0; i < power; i++)
        {
            *result = *result * num;
        }
        *result = 1 / *result;
    }
}
