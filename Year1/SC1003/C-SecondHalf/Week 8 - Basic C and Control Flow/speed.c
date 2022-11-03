#include <stdio.h>

int main()
{
    int trial = 0;
    int i = 0;
    float time, distance, speed;
    printf("Enter the number of times:\n");
    scanf("%d", &trial);
    while (i < trial)
    {
        printf("Enter distance (in km):\n");
        scanf("%f", &distance);
        printf("Enter time (in sec):\n");
        scanf("%f", &time);
        speed = distance / time;
        printf("The speed is %.2f km/sec\n", speed);
        i = ++i;
    }

    return 0;
}