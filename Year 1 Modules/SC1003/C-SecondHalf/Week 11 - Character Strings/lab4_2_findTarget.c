/*(findTarget) Write a C program that reads and searches character strings. In the program, it
contains the function findTarget() that searches whether a target name string has been
stored in the array of strings.*/
#include <stdio.h>
#include <string.h>
#define SIZE 10
#define INIT_VALUE 999
void printNames(char nameptr[][80], int size);
void readNames(char nameptr[][80], int *size);
int findTarget(char *target, char nameptr[][80], int size);
int main()
{
    char nameptr[SIZE][80], t[40], *p;
    int size, result = INIT_VALUE;
    int choice;

    printf("Select one of the following options: \n");
    printf("1: readNames()\n");
    printf("2: findTarget()\n");
    printf("3: printNames()\n");
    printf("4: exit()\n");
    do
    {
        printf("Enter your choice: \n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            readNames(nameptr, &size);
            break;
        case 2:
            printf("Enter target name: \n");
            scanf("\n");
            fgets(t, 80, stdin);
            if (p = strchr(t, '\n'))
                *p = '\0';
            result = findTarget(t, nameptr, size);
            printf("findTarget(): %d\n", result);
            break;
        case 3:
            printNames(nameptr, size);
            break;
        }
    } while (choice < 4);
    return 0;
}
void printNames(char nameptr[][80], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%s ", nameptr[i]);
    printf("\n");
}
void readNames(char nameptr[][80], int *size)
{
    int row;
    printf("Enter size:\n");
    scanf("%d", size);
    printf("Enter %d name:\n", *size);
    for (row = 0; row < *size; row++)
    {
        scanf("%s", nameptr[row]);
    }
}
int findTarget(char *target, char nameptr[][80], int size)
{
    int row;
    for(row = 0; row < size; row++)
    {
        if(strcmp(nameptr[row], target) == 0)
            return row;
    }

    return -1;
}