/*Write a C function maxCharToFront() that accepts a character string str as parameter, finds the
largest character from the string (based on ASCII value), and moves it to the beginning of the
string. E.g., if the string is "adecb", then the string will be "eadcb" after executing the function.
The string will be passed to the caller via call by reference. If more than one largest character is
in the string, then the  first appearance of the largest character will be moved to the beginning
of the string. For example, if the string is "adecbe", then the resultant string will be "eadcbe".*/
#include <stdio.h>
#include <string.h>
void maxCharToFront(char *str);
int main()
{
    char str[80], *p;

    printf("Enter a string: \n");
    fgets(str, 80, stdin);
    if (p = strchr(str, '\n'))
        *p = '\0';
    printf("maxCharToFront(): ");
    maxCharToFront(str);
    puts(str);
    return 0;
}
void maxCharToFront(char *str)
{
    char max;
    char *ptr;
    ptr = str;
    max = str[0];
    int i = 0;
    while (str[i] != '\0')
    {
        if (max < str[i])
        {
            max = str[i];
            ptr = &str[i];
        }
        i++;
    }
    while (ptr > str)
    {
        *ptr = *(ptr - 1);
        ptr--;
    }
    str[0] = max;
}