/*Write a C function that locates the last occurrence of ch in the string pointed to by s. The
function returns a pointer to the character, or a null pointer if ch does not occur in the string.
Write the code for the function without using any of the standard library string functions.*/

#include <stdio.h>
#include <string.h>

char *stringrChr(char *s, char ch);

int main()
{
    char s[128], c, *p;
    char *temp = NULL;

    printf("Enter a string: \n");
    fgets(s, 80, stdin);
    if (p = strchr(s, '\n'))
        *p = '\0';
    printf("Enter a character: \n");
    scanf("%c", &c);
    temp = stringrChr(s, c);
    if (temp != NULL)
        printf("StringrChr(): %s \n", temp);
    else
        printf("StringrChr(): null string\n");
    return 0;
}

char *stringrChr(char *s, char ch)
{
    int length = 0, i;
    while (*s != '\0')
    {
        s++;
        length++;
    }
    for (i = 0; i < length; i++)
    {
        if (*(--s) == ch)
            return s;
    }
    return NULL;
}