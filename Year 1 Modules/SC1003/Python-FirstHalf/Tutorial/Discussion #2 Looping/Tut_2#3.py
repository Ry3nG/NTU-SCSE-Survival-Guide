import math

"""
width = int(input("Please enter pattern width: "))

#display the first 5 rows of the pattern

for i in range(1, width+1):
    for j in range(i):
        print("*" , end='')
    print() 

for i in range(width-1,0,-1):
    for j in range(i):
        print("*" , end='')
    print() 

"""
"""
# method 2
width = int(input("Please enter pattern width: "))

for i in range(1, width*2):
    if i < width:
        count = i
    else:
        count = width*2-i
    for j in range(count):
        print("*" , end='')
    print() 
"""
#method 3

width = int(input("Please enter pattern"))

for i in range(1, width+1):
    print(i * "*")
for i in range(width-1, 0,-1 ):
    print(i * "*")

    