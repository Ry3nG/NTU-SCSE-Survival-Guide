#include <stdio.h>
int main()
{
    float hoursOfWork, grossPay, tax, netPay;
    float payRate = 6.0, payRateOverTime = 1.5 * 6;
    float taxRate = 0.1, taxRate2 = 0.2, taxRate3 = 0.3;
    int overTimeValue = 40, tax1 = 1000, tax2 = 500;
    printf("Enter hours of work: \n");
    scanf("%f", &hoursOfWork);
    if (hoursOfWork <= overTimeValue)
    {
        grossPay = hoursOfWork * payRate;
        if (grossPay <= tax1)
        {
            tax = taxRate * grossPay;
        }
        else if (grossPay > tax1 && grossPay <= (tax1 + tax2))
        {
            tax = taxRate * tax1 + taxRate2 * (grossPay - tax1);
        }
        else
        {
            tax = taxRate * tax1 + taxRate2 * tax2 + (grossPay - (tax1 + tax2)) * taxRate3;
        }
    }
    else
    {
        grossPay = 40 * 6 + (hoursOfWork - 40) * payRateOverTime;
        if (grossPay <= tax1)
        {
            tax = taxRate * grossPay;
        }
        else if (grossPay > tax1 && grossPay <= (tax1 + tax2))
        {
            tax = taxRate * tax1 + taxRate2 * (grossPay - tax1);
        }
        else
        {
            tax = taxRate * tax1 + taxRate2 * tax2 + (grossPay - (tax1 + tax2)) * taxRate3;
        }
    }
    netPay = grossPay - tax;
    printf("Gross pay  = %.2f\n", grossPay);
    printf("Tax = %.2f\n", tax);
    printf("Net pay = %.2f\n", netPay);
    return 0;
}