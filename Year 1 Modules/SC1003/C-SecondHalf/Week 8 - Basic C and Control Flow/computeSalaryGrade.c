#include <stdio.h>
int main()
{
    int salary, merit;
    printf("Enter the salary:\n");
    scanf("%d", &salary);
    printf("Enter the merit: \n");
    scanf("%d", &merit);
    if (500 <= salary && salary < 600)
    {
        printf("The grade: C\n");
    }
    else if (600 <= salary && salary <= 649)
    {
        if (merit < 10)
        {
            printf("The grade: C\n");
        }
        else
        {
            printf("The grade: B\n");
        }
    }
    else if (650 <= salary && salary < 700)
    {
        printf("The grade: B\n");
    }
    else if (700 <= salary && salary <= 799)
    {
        if (merit < 20)
        {
            printf("The grade: B\n");
        }
        else
        {
            printf("The grade: A\n");
        }
    }
    else
    {
        printf("The grade: A\n");
    }
    return 0;
}