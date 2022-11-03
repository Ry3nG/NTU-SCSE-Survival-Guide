"""
Consider a system for storing anonymous grades of each lab class.
Define a data structure, which can identify individuals in each lab group by an ID number 1-40 (inclusive).
To identify the person in the entire class you would also need the group name, e,g., ‘FE2’.
Each corresponding person should have a number between 1-100 (inclusive) to define grade.
"""
import math

#use dictionary, tuple as keys
grades = {
    ("FS1" , 1) : 45,
    ("FS1" , 2) : 75,
    ("FS1" , 3) : 85,
    ("FS1" , 4) : 100,

    ("FS2" , 1) : 75,
    ("FS2" , 2) : 85,
    ("FS2" , 3) : 100,
    ("FS2" , 4) : 25

}

print(grades[("FS1",2)])

"""
#solution 2:

grades = {
    'FS1':[45,75,85,100],
    'FS2':[75,85,100,25]

}

print(grades['FS1'][1])

"""