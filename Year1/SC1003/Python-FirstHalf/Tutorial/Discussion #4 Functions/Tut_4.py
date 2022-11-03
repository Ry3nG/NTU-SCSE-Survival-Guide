import math
import time

#configuration
list_of_grades = []
max_grade = []
quit_database = False


#database functions
def inputRecord(database, group, id, score):
    database = grades
    grades[group, id] = score
    print("Input Successful")
    print("Current database: ", database)
    print()


def query(database, group, id):
    database = grades
    print("Student", id, "'s score is:", grades[group, id])
    print()


def listGrades(database, group):
    database = grades
    list_of_grades = []
    for x in grades.keys():
        if group in x:
            list_of_grades.append(grades[x])
    print("The list of grades in group", group, "is", list_of_grades)

    print()


def maxGrade(database, group):
    database = grades
    max_grade = []
    for x in grades.keys():
        if group in x:
            max_grade.append(grades[x])
    print("Highest grade in group", group, "is", max(max_grade))
    print()


def error_message():
    print(
        "Input error, directing to the main menu... Please follow the instructions."
    )
    print()
    time.sleep(2)


#database, use dictionary, tuple as keys.
grades = {
    ("G1", 1): 45,
    ("G1", 2): 75,
    ("G1", 3): 85,
    ("G1", 4): 120,
    ("G2", 1): 75,
    ("G2", 2): 85,
    ("G2", 3): 100,
    ("G2", 4): 25
}

#main program

while quit_database == False:
    print("Welcome back to the grading system! Please enter your option:")
    print("1: Input a record.")
    print("2: Query a student.")
    print("3: List grades in a group.")
    print("4: Get the max score in a group.")
    print("5: Exit.")
    print()

    option = int(input("Option: "))

    try:
        if option == 1:
            group = input("Please input the group number (G1/G2): ")
            print("You entered", group)
            id = int(input("Please input the student's id: "))
            score = int(input("Please input the score of the student: "))
            inputRecord(grades, group, id, score)
    except:
        error_message()
        continue

    try:
        if option == 2:
            group = input("Please input the group number (G1/G2): ")
            id = int(input("Please input the student's id: "))

            query(grades, group, id)
    except:
        error_message()
        continue

    try:
        if option == 3:
            group = input("Please input the group number (G1/G2): ")

            listGrades(grades, group)
    except:
        error_message()
        continue

    try:
        if option == 4:
            group = input("Please input the group number (G1/G2): ")

            maxGrade(grades, group)
    except:
        error_message()
        continue

    if option == 5:
        print("Goodbye~")
        exit()