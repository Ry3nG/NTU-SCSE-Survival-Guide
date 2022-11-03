#include <stdio.h>

void readInput(int *id, int *noOfHours, int *payRate);
double computeSalary1(int noOfHours, int payRate);
void computeSalary2(int noOfHours, int payRate, double *grossPay);

int main()
{
    int id = -1, noOfHours, payRate;
    double grossPay;

    readInput(&id, &noOfHours, &payRate);
    while (id != -1)
    {
        printf("ComputerSalary1(): ");
        grossPay = computeSalary1(noOfHours, payRate);
        printf("ID %d grossPay %.2f\n", id, grossPay);

        printf("ComputeSalary2():");
        printf("ID %d grossPay %.2f\n", id, grossPay);

        readInput(&id, &noOfHours, &payRate);
    }
    return 0;
}

void readInput(int *id, int *noOfHours, int *payRate)
{
    printf("Enter ID (-1 to end):\n");
    scanf("%d", &*id);
    if(*id != -1)
    {
    printf("Enter the number of hours:\n");
    scanf("%d", &*noOfHours);
    printf("Enter hourly pay rate:\n");
    scanf("%d", &*payRate);
    }
}
double computeSalary1(int noOfHours, int payRate)
{
    double grossPay;
    if (noOfHours > 160)
    {
        grossPay = (noOfHours - 160) * (payRate * 1.5) + (160 * payRate);
    }
    else
    {
        grossPay = noOfHours * payRate;
    }
    return grossPay;
}
void computeSalary2(int noOfHours, int payRate, double *grossPay)
{
    if (noOfHours > 160)
    {
        *grossPay = (noOfHours - 160) * (payRate * 1.5) + (160 * payRate);
    }
    else
    {
        *grossPay = noOfHours * payRate;
    }
}