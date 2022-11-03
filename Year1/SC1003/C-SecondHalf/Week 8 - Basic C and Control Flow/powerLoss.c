#include <stdio.h>
int main()
{
    int time = 0, num = 0;
    float i, r, powerloss;
    printf("Enter the number of times:\n");
    scanf("%d", &time);
    for (num = 0; num < time; num += 1)
    {
        printf("Enter the current:\n");
        scanf("%f", &i);
        printf("Enter the resistance: \n");
        scanf("%f", &r);
        powerloss = i * i * r;
        printf("The power loss is: %.2f\n", powerloss);
    }
    return 0;
}