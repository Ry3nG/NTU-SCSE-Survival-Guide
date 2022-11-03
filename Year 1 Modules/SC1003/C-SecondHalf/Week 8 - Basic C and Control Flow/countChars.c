#include <stdio.h>
int main()
{
    char res;
    int numDigits = 0;
    int letterDigits = 0;
    printf("Enter your characters (# to end)\n");
    while (res != 35)
    {
        res = getchar();
        if (48 <= res && res <= 57)
        {
            numDigits = numDigits + 1;
        }
        else if (65 <= res && res<= 90 || 97 <= res && res<= 122)
        {
            letterDigits = letterDigits + 1;
        }
    }
    printf("The number of digits: %d\n", numDigits);
    printf("The number of letters: %d\n", letterDigits);
    return 0;
}