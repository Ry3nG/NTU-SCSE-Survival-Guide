/* Write a C function that accepts an English sentence as parameter, and returns the length of the
longest word in the sentence. For example, if the sentence is "I am happy.", then the length of
the longest word "happy" in the sentence 5 will be returned. Assume that each word is a
sequence of English letters.*/
#include <stdio.h>
#include <string.h>

int longWordLength(char *s);

int main()
{
    char str[80], *p;

    printf("Enter a string: \n");
    fgets(str, 80, stdin);
    if (p = strchr(str, '\n'))
        *p = '\0';
    printf("longWordLength(): %d\n", longWordLength(str));
    return 0;
}
int longWordLength(char *s)
{
    int count = 0;
    int countMax = 0;
    int i;
    int length;
    length = strlen(s);
    for (i = 0; i < length+1; i++)
    {

        if (!((65<=s[i]&& s[i]<=90)||(97<=s[i]&& s[i]<=122)))
        {
            if (countMax < count)
                countMax = count;
            count = 0;
        }
        else
        {
            count++;
        }
    }
    return countMax;
}