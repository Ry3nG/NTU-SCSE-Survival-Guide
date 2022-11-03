#include <stdio.h>
#include <math.h>

int main()
{
    float a1, a2, b1, b2, c1, c2;
    float x, y;
    printf("Enter a1, b1, c1, a2, b2, c2\n");
    scanf("%f %f %f %f %f %f", &a1, &b1, &c1, &a2, &b2, &c2);
    if ((a1 * b2 - a2 * b1) == 0 || (a1 * b2 - a2 * b1) == 0)
    {
        printf("Dominator is Zero!\n");
    }
    else
    {
        x = (b2 * c1 - b1 * c2) / (a1 * b2 - a2 * b1);
        y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
        printf("x = %.2f, y = %.2f \n", x, y);
    }

    return 0;
}