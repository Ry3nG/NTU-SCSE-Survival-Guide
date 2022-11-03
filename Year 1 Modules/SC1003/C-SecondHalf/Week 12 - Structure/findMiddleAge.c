/*Write a function that takes in an array of three persons, finds the person whose age is the
middle one of the three persons, and returns the name and age of that person to the caller. For
example, if the array is {{"Tom",18},{"John",19}, {"Jim",20}}, then the person John and his age
will be returned. In this question, you may assume that the three persons have different ages.*/
#include <stdio.h>
typedef struct
{
    char name[20];
    int age;
} Person;

void readData(Person *p);
Person findMiddleAge(Person *p);

int main()
{
    Person man[3], middle;
    readData(man);
    middle = findMiddleAge(man);
    printf("findMiddleAge(): %s %d\n", middle.name, middle.age);
    return 0;
}

void readData(Person *p)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        printf("Enter person %d: \n", i + 1);
        scanf("%s", p[i].name);
        scanf("%d", &p[i].age);
    }
}
Person findMiddleAge(Person *p)
{
    int i;
    int least = p[0].age, most = p[0].age;
    for (i = 1; i < 3; i++)
    {
        if (least > p[i].age)
            least = p[i].age;
        if (most < p[i].age)
            most = p[i].age;
    }
    for (i = 0; i < 3; i++)
    {
        if (p[i].age != least && p[i].age != most)
            return p[i];
    }
}