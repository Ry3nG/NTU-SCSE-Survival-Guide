/*Write a C function average() that creates a database of maximum 50 students using an array
of structures. The function reads in student name. For each student, it takes in the test
score and exam score. Then it computes and prints the total score of the student. The input
will end when the student name is "END". Then, it computes and returns the average score
of all students to the calling function (i.e. main()). The calling function then prints the
average score on the display.*/

#include <stdio.h>
#include <string.h>

struct student
{
    char name[20];    /* student name */
    double testScore; /* test score */
    double examScore; /* exam score */
    double total;     /* total = (testScore+examScore)/2 */
};

double average();

int main()
{
    printf("average(): %.2f\n", average());
    return 0;
}
double average()
{
    struct student db[50];
    int i = 0;
    double sum = 0;
    char *ptr;
    puts("Enter student name:");
    fgets(db[i].name, 20, stdin);
    if (ptr = strchr(db[i].name, '\n'))
        *ptr = '\0';
    while (strcmp(db[i].name, "END") != 0 && i < 50)
    {
        puts("Enter test score:");
        scanf("%lf", &db[i].testScore);
        puts("Enter exam score:");
        scanf("%lf", &db[i].examScore);
        getchar();
        db[i].total = (db[i].testScore + db[i].examScore) / 2;
        sum += db[i].total;
        printf("Student %s total = %.2lf\n", db[i].name, db[i].total);
        i++;
        puts("Enter student name:");
        fgets(db[i].name, 20, stdin);
        if (ptr = strchr(db[i].name, '\n'))
            *ptr = '\0';
    }
    return i == 0 ? 0.0 : sum / i;
}