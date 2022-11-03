#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// memory
int *r;

void print_pos(int rlength, int first_cut[])
{
    if (rlength == 0)
        return;
    int pos = first_cut[rlength];
    printf("%d ", pos);
    print_pos(rlength - pos, first_cut);
}

int cr_bottom_up_dp_print(int *p, int n)
{
    int i, j;
    r[0] = 0;

    int firstCut[n + 1];
    for (i = 0; i <= n; i++)
        firstCut[i] = 0;

    for (i = 0; i <= n; i++)
    {
        int position = 0;
        for (j = 0; j <= i; j++)
        {
            int temp = p[j] + r[i - j];
            if (temp > r[i])
            {
                position = j;
                r[i] = temp;
            }
            firstCut[i] = position;
        }
    }
        printf("Length of each piece is:\n");
        print_pos(n, firstCut);
        printf("\n");
        return r[n];
}
    void main()
    {
        int n; // length of  rod
        int function;
        int i;
        int *p; // price list

        int price_list[10] = {0, 1, 4, 8, 9, 10, 17, 17, 20, 24}; // declare one more value to cover the index 0;

        n = sizeof(price_list) / sizeof(int) - 1;
        p = price_list;

        // allocate the memory array
        r = malloc(sizeof(int) * (n + 1));

        // set all memory elements to -1
        for (i = 0; i <= n; i++)
            r[i] = -1;

        printf("The maximun value is: %d \n", cr_bottom_up_dp_print(p, n));
    }