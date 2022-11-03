#include <stdio.h>
int main()
{
    int numOfLines;
    int i;
    float average = 0, sum = 0, num = 0;
    int counter = 0;

    printf("Enter number of lines:\n");
    scanf("%d", &numOfLines);
    for (i = 1; i <= numOfLines; i++)
    {
        printf("Enter line %d (end with -1):\n", i);
        average = 0, sum = 0, num = 0, counter = 0;
        while(1)
        {
            scanf("%f", &num);
            if(num == -1)
            {
                break;
            }
            sum = sum + num;
            counter += 1;
        }
        average = (sum) / (counter);
        printf("Average = %.2f\n", average);
    }
    return 0;
}