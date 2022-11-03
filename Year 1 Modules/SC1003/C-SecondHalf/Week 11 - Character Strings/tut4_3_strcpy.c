#include <stdio.h>
/*Write the function strncpy() that copies not more than n characters (characters that follow a
null character are not copied) from the array pointed to by s2 to the array pointed to by s1.
If the array pointed to by s2 is a string shorter than n characters, null characters are
appended to the copy in the array pointed to by s1, until n characters in all have been
written.  The strncpy returns the value of s1.
*/
char *strncpy(char *s1, char *s2, int n);

int main()
{
    char s1[80], s2[80];
    int i, n;
    printf("Enter the string.\n");
    fgets(s2, 80, stdin);
    for (i = 0; i < 80; i++)
    {
        if (s2[i] == '\n')
            s2[i] = '\0';
    }
    printf("Enter the number of characters: \n");
    scanf("%d", &n);
    printf("strncpy(): %s\n", strncpy(s1, s2, n));
    return 0;
}

char *strncpy(char *s1, char *s2, int n)
{
    int i = 0;
    while (s2[i] != '\0')
    {
        if (i < n)
            s1[i] = s2[i];
        else
            return s1;
        i++;
    }
    return s1;
}