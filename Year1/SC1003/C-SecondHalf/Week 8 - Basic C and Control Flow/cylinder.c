#include <stdio.h>
#define Pi 3.1416

int main()
{
    float r, h;
    float volume, area;
    int time;
    printf("Enter the number of times:\n");
    scanf("%d", &time);
    for (int i = 0; i < time; i++)
    {
        printf("Enter the radius:\n");
        scanf("%f", &r);
        printf("Enter the height:\n");
        scanf("%f", &h);
        volume = Pi * (r * r) * h;
        area = 2 * Pi * r * h + 2 * Pi * r * r;
        printf("The volume is: %.2f\n", volume);
        printf("The surface area is: %.2f\n", area);
    }

    return 0;
}