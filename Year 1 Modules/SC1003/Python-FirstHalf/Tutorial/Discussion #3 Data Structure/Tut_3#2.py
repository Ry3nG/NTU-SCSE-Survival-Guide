import math

strong = False
password = input("Enter your password： ")

while not strong:
        if password.find(' ') != -1:
            print("Invalid password, space is not allowed.")
            password = input("Please enter a valid password： ")

        elif len(password) <= 7:
            print("Your Password should contain at least 8 characters.")
            password = input("Please enter a valid password： ")

        elif password.isalpha() == True:
            print("Your Password must contain numbers and letters.")
            password = input("Please enter a valid password： ")

        elif password.isdigit() == True:
            print("Your Password must contain numbers and letters.")
            password = input("Please enter a valid password： ")

        elif password.islower() == True:
            print("Your Password must contain upper and lower cased characters.")
            password = input("Please enter a valid password： ")

        else:
            strong = True
            break

print("Your Password is valid.")
print(password)