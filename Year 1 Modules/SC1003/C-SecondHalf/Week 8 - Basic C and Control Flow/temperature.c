#include <stdio.h>
int main()
{
    float tempF, tempC;
    while (1)
    {
        printf("Enter the temperature in degree F:\n");
        scanf("%f", &tempF);
        if (tempF == -1)
        {
            break;
        }
        tempC = (5.0 / 9.0) * (tempF - 32);
        printf("Converted degree in C: %.2f\n", tempC);
    }

    return 0;
}