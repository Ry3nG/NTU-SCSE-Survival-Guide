#include <stdio.h>
int main()
{
    char res;
    printf("Enter a character:\n");
    res = getchar();
    if (65 <= res && res <= 90)
    {
        printf("Upper case letter\n");
    }
    else if (97 <= res && res <= 122)
    {
        printf("Lower case letter\n");
    }
    else if(48 <= res && res <= 57)
    {
        printf("Digit\n");
    }
    else
    {
        printf("Other character");
    }
    return 0;
}
