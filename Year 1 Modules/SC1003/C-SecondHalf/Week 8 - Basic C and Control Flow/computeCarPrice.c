#include <stdio.h>

int main()
{
    float listPrice, luxuryTax = 0.1, gstTax = 0.03, discount = 0.9, taxedPrice;
    char category;
    printf("Please enter the list price: \n");
    scanf("%f", &listPrice);
    if (listPrice * discount <= 100000)
    {
        taxedPrice = listPrice * discount * gstTax + listPrice * discount;
    }
    else
    {
        taxedPrice = listPrice * discount * luxuryTax + listPrice * gstTax * discount + listPrice * discount;
    }
    printf("Please enter the category: \n");
    scanf("%s", &category);
    switch (category)
    {
    case '1':
        printf("Total price is: %.2f", taxedPrice + 70000);
        break;
    case '2':
        printf("Total price is: %.2f", taxedPrice + 80000);
        break;
    case '3':
        printf("Total price is: %.2f", taxedPrice + 23000);
        break;
    case '4':
        printf("Total price is: %.2f", taxedPrice + 600);
        break;
    default:
        printf("You didn't enter the right category, your price excluding COE is: %.2f", taxedPrice);
    }
    return 0;
}