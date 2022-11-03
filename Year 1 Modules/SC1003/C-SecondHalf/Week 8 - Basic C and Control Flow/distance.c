#include <stdio.h>
#include <math.h>

int main()
{
    int time;
    double x1, y1, x2, y2;
    double distance;
    printf("Enter the number of times: \n");
    scanf("%d", &time);
    for (int i = 0; i < time; i++)
    {
        printf("Enter first point x1 y1: \n");
        scanf("%lf %lf", &x1, &y1);
        printf("Enter second point x2 y2: \n");
        scanf("%lf %lf", &x2, &y2);
        distance =  sqrt((pow(x1 - x2, 2) + pow(y1 - y2, 2)));
        printf("The distance is: %.2lf\n", distance);
    }
    return 0;
}