# two ways to do this
import math

count = 0
str = input("enter a string: ")

while str != "####":
    if "a" in str:
        count +=1
    str = input("enter a string: ")

print(count, "strings with letter 'a'")

"""count = 0

str = input("Enter a string (enter #### to stop): ")
while str != "####":
    for letter in str:
        if letter == "a":
            count +=1
            break
    str = input("Enter a string (enter #### to stop): ")

print(count, "strings with letter 'a'")"""
