/*
 * @Author: Ryan, Gong Zerui
 * @Date: 2021-11-04 16:50:16
 * @Last Modified by: Ryan, Gong Zerui
 * @Last Modified time: 2021-11-04 22:54:33
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 5
#define INT_MAX 2147483647

typedef struct
{
    int nameCardID;
    char personName[20];
    char companyName[20];
} NameCard;

void initialize(NameCard *p);
void listNameCards(NameCard *p, int *slot);
int addNameCard(NameCard *p, int *slot);
int removeNameCard(NameCard *p, int *slot);
int getNameCard(NameCard *p, int *slot);
void bubbleSort(NameCard *p, int num);
int strmixcmp(const char *s1, const char *s2);

int main()
{
    NameCard database[MAX];
    int choice;
    int result;
    int slot = 0;
    initialize(database);
    puts("NTU NAME CARD HOLDER MANAGEMENT PROGRAM:");
    puts("1: listNameCards()");
    puts("2: addNameCard()");
    puts("3: removeNameCard()");
    puts("4: getNameCard()");
    puts("5: quit");
    do
    {
        printf("Enter your choice: \n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            listNameCards(database, &slot);
            break;
        case 2:
            result = addNameCard(database, &slot);
            if (result == 0)
            {
                bubbleSort(database, slot);
                puts("The name card has been added successfully");
            }
            else if (result == 1)
                puts("The name card holder is full");
            else if (result == 2)
                puts("The nameCardID has already existed");
            break;
        case 3:
            result = removeNameCard(database, &slot);
            if (result == 0)
            {
                bubbleSort(database, slot);
                slot -= 1;
            }
            else if (result == 1)
                puts("The name card holder is full");
            else if (result == 2)
                puts("The target person name is not in the name card holder");
            else if (result == 3)
                puts("The name card holder is empty");
            break;
        case 4:
            result = getNameCard(database, &slot);
            if (result == 1)
                puts("The target person name is not found ");
            break;
        }
    } while (choice < 5);
    return 0;
}

void initialize(NameCard *p)
{
    int i;
    for (i = 0; i < MAX; i++)
        p[i].nameCardID = INT_MAX;
}

void listNameCards(NameCard *p, int *slot)
{
    int i;
    puts("listNameCards():");
    // check whether the database is empty
    if (*slot == 0)
        puts("The name card holder is empty");
    else
    {
        for (i = 0; i < *slot; i++)
        {
            printf("nameCardID: %d\n", p[i].nameCardID);
            printf("personName: %s\n", p[i].personName);
            printf("companyName: %s\n", p[i].companyName);
        }
    }
}

int addNameCard(NameCard *p, int *slot)
{
    int i;
    char *character;
    char dummychar[20];
    NameCard buffer;
    puts("addNameCard():");
    puts("Enter nameCardID: ");
    scanf("%d", &buffer.nameCardID);
    puts("Enter personName: ");
    fgets(dummychar, 20, stdin);
    fgets(buffer.personName, 20, stdin);
    if (character = strchr(buffer.personName, '\n'))
        *character = '\0';
    puts("Enter companyName: ");
    fgets(buffer.companyName, 20, stdin);
    if (character = strchr(buffer.companyName, '\n'))
        *character = '\0';
    //check whether the database is full, then try to move the information into the database
    if (*slot == MAX)
        return 1;
    else
    {
        p[*slot].nameCardID = buffer.nameCardID;
        strcpy(p[*slot].personName, buffer.personName);
        strcpy(p[*slot].companyName, buffer.companyName);
    }

    //check whether already have a same id
    for (i = 0; i < *slot; i++)
        if (p[i].nameCardID == p[*slot].nameCardID)
            return 2;
    if (*slot < MAX)
        *slot += 1;
    return 0;
}

int removeNameCard(NameCard *p, int *slot)
{
    char target[20], *ptr, dummychar[20];
    int i, j;
    puts("removeNameCard():");
    puts("Enter personName:");
    //check whether the database is full
    if (*slot == MAX)
        return 1;
    fgets(dummychar, 20, stdin);
    fgets(target, 20, stdin);
    if (ptr = strchr(target, '\n'))
        *ptr = '\0';
    // check whether the database is empty
    if (*slot == 0)
        return 3;
    for (i = 0; target[i] != '\0'; i++)
    {
        if (target[i] >= 'a' && target[i] <= 'z')
            target[i] = target[i] - 32;
    }

    for (i = 0; i < *slot; i++)
    {
        if (strmixcmp(target, p[i].personName) == 0)
        {
            puts("The name card is removed");
            printf("nameCardID: %d\n", p[i].nameCardID);
            printf("personName: %s\n", p[i].personName);
            printf("companyName: %s\n", p[i].companyName);
            p[i].nameCardID = INT_MAX;
            return 0;
        }
    }
    return 2;
}

int getNameCard(NameCard *p, int *slot)
{
    int i;
    char target[20], *ptr, dummychar[20];
    puts("getNameCard():");
    puts("Enter personName:");
    fgets(dummychar, 20, stdin);
    fgets(target, 20, stdin);
    if (ptr = strchr(target, '\n'))
        *ptr = '\0';

    for (i = 0; target[i] != '\0'; i++)
    {
        if (target[i] >= 'a' && target[i] <= 'z')
            target[i] = target[i] - 32;
    }
    for (i = 0; i < *slot; i++)
    {
        if (strmixcmp(target, p[i].personName) == 0)
        {
            puts("The target person name is found ");
            printf("nameCardID: %d\n", p[i].nameCardID);
            printf("personName: %s\n", p[i].personName);
            printf("companyName: %s\n", p[i].companyName);
            return 0;
        }
    }
    return 1;
}

void bubbleSort(NameCard *p, int num)
{
    int i, j;
    NameCard temp;
    for (i = 0; i < num - 1; i++)
    {
        for (j = 0; j < (num - i - 1); j++)
        {
            if (p[j].nameCardID > p[j + 1].nameCardID)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int strmixcmp(const char *s1, const char *s2) //s1 is all upper case, s2 is mix-cased
{
    int i;
    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
    {
        if (s1[i] != s2[i] && s1[i] != s2[i] - 32)
        {
            return -1;
        }
    }
    return 0;
}