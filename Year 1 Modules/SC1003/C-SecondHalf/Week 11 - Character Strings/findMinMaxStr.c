/*Write a C function that reads in words separated by space, finds the first and last words
according to ascending alphabetical order (based on ASCII values), and returns them to the
calling function through the string parameters first and last. The calling function will then print
the first and last strings on the screen.*/
#include <stdio.h>
#include <string.h>
#define SIZE 10
void findMinMaxStr(char word[][40], char *first, char *last, int size);
int main()
{
    char word[SIZE][40];
    char first[40], last[40];
    int i, size;

    printf("Enter size: \n");
    scanf("%d", &size);
    printf("Enter %d words: \n", size);
    for (i = 0; i < size; i++)
        scanf("%s", word[i]);
    findMinMaxStr(word, first, last, size);
    printf("First word = %s, Last word = %s\n", first, last);
    return 0;
}
void findMinMaxStr(char word[][40], char *first, char *last, int size)
{
    int i;
    strcpy(first, word[0]);
    strcpy(last, word[0]);
    for (i = 1; i < size; i++)
    {
        if (strcmp(word[i], first) < 0)
            strcpy(first, word[i]); //!!!no first = word[i] must use strcpy()!!!!!!
        if (strcmp(word[i], last) > 0)
            strcpy(last, word[i]);
    }
}