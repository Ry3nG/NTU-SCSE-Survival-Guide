#include <stdio.h>
//----------------------------------------------------------------
// function prototypes
double computePay1(int noOfHours, int payRate);
void computePay2(int noOfHours, int payRate, double *grossPay);
//----------------------------------------------------------------
int main()
{
    int noOfHours, payRate;
    double grossPay;

    printf("Enter the number of hours:\n");
    scanf("%d", &noOfHours);
    printf("Enter hourly pay rate:\n");
    scanf("%d", &payRate);
    printf("computePay(1): %.2f\n", computePay1(noOfHours, payRate));
    computePay2(noOfHours, payRate, &grossPay);
    printf("ComputePay(2): %.2f\n", grossPay);

    return 0;
}
//----------------------------------------------------------------
double computePay1(int noOfHours, int payRate)
{
    double grossPay;
    if (noOfHours>160)
    {
        grossPay = (noOfHours - 160)*(payRate*1.5) + (160*payRate);
    }
    else
    {
        grossPay = noOfHours* payRate;
    }
    return grossPay;
}
void computePay2(int noOfHours, int payRate, double *grossPay)
{
    if(noOfHours>160)
    {
        *grossPay = (noOfHours - 160)*(payRate*1.5) + (160*payRate);
    }
    else
    {
        *grossPay = noOfHours* payRate;
    }
}
