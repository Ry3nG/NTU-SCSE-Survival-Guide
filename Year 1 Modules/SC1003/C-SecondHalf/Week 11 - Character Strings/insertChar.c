/* Write the C function that takes in a string str1 as an argument, copies the contents of
character string str1 into character string str2. In addition, the function also has a character
parameter ch. For every three characters copied from str1 to str2, the character ch is
inserted into str2. The function  returns the resultant string to the calling function via call
by reference. For example, if the string str1 is "abcdefg", and the inserted character ch is
‘#’, then the resultant string str2 = "abc#def#g" will be returned to the calling function.*/
#include <stdio.h>
#include <string.h>

void insertChar(char *str1, char *str2, char ch);

int main()
{
    char a[80], b[80];
    char ch, *p;

    printf("Enter a string: \n");
    fgets(a, 80, stdin);
    if (p = strchr(a, '\n'))
        *p = '\0';
    printf("Enter a character to be inserted: \n");
    ch = getchar();
    insertChar(a, b, ch);
    printf("insertChar(): ");
    puts(b);
    return 0;
}

void insertChar(char *str1, char *str2, char ch)
{
    int i, k;
    k = 0;
    while (*str1 != '\0')
    {
        for (i = 1; i <= 3 && *str1; i++)
        {
            str2[k] = *str1;
            k++;
            str1++;
        }
        if (i == 4)
        {
            str2[k] = ch;
            k++;
        }
    }
    str2[k] = '\0';
}