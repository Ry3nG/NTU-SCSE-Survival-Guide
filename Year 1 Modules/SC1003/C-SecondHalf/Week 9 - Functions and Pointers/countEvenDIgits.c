#include <stdio.h>

int countEvenDigit1(int number);
void countEvenDigit2(int number, int *count);

int main(){
    int number, result;
    printf("Enter the number: \n");
    scanf("%d", &number);
    printf("countEvenDigit1(): %d\n", countEvenDigit1(number));
    countEvenDigit2(number, &result);
    printf("countEvenDigit2(): %d\n", result);
    return 0;
}

int countEvenDigit1(int number)
{
    int result = 0;
    do
    {
        if(number%2 == 0){
            result ++;
        }
        number = number/10;
    } while(number);
    return result;
}

void countEvenDigit2(int number, int *count)
{
    do
    {
        if(number % 2 == 0){
            *count = *count+1;
        }
        number = number/10;
    }while(number);
}
