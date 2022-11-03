/*Write a C function that compares the string pointed to by s1 to the string pointed to by s2. If
the string pointed to by s1 is greater than, equal to, or less than the string pointed to by s2,
then it returns 1, 0 or –1 respectively. Write the code for the function without using the
standard C string library function strcmp().*/

#include <stdio.h>
int stringcmp(char *s1, char *s2);
int main()
{
    char s1[80], s2[80];
    int i = 0, j = 0;
    printf("Enter a source string: \n");
    fgets(s1, 80, stdin);
    for (i = 0; i < 80; i++)
    {
        if (s1[i] == '\n')
            s1[i] = '\0';
    }
    printf("Enter a target string: \n");
    fgets(s2, 80, stdin);
    for (i = 0; i < 80; i++)
    {
        if (s2[i] == '\n')
            s2[i] = '\0';
    }
    switch (stringcmp(s1, s2))
    {
    case 1:
        printf("stringcmp(): greater than\n");
        break;
    case 0:
        printf("stringcmp(): equal\n");
        break;
    case -1:
        printf("stringcmp(): less than\n");
        break;
    default:
        printf("ERROR!");
    }
    return 0;
}
int stringcmp(char *s1, char *s2)
{
    int i, j;
    while (s1[i] != '\0' && s2[i != '\0'])
    {
        if (s1[i] > s2[i])
            return 1;
        else if (s1[i] < s2[i])
            return -1;
        else
            i++, j++;
    }
    if (s1[i] == '\0' && s2[i] != '\0')
        return -1;
    else if (s1[i] != '\0' && s2[i] == '\0')
        return 1;
    else
        return 0;
}