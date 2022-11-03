#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int *result;

int top_down_dp(int n)
{
    if (n == 0)
    {
        result[0] = 0;
        return 0;
    }
    else if (n == 1)
    {
        result[1] = 1;
        return 1;
    }
    else if (n == 2)
    {
        result[2] = 2;
        return 2;
    }

    if (result[n - 1] == -1)
        result[n - 1] = top_down_dp(n - 1);
    if (result[n - 2] == -1)
        result[n - 2] = top_down_dp(n - 2);
    if (result[n - 3] == -1)
        result[n - 3] = top_down_dp(n - 3);

    result[n] = result[n - 1] + 2 * result[n - 2] - 3 * result[n - 3];

    return result[n];
}

int main()
{
    int n;
    int function;
    int i;
    int j;
    printf("Enter the value of n:\n");
    scanf("%d", &n);

    result = malloc(sizeof(int[n+1][n+1]));
    for (i = 0; i <= n; i++)
    {
        result[i] = -1;
    }
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
}