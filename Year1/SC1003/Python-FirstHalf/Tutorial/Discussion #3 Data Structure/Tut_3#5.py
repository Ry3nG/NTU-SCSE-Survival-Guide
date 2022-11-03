import math

"""
list1=[]

for i in range(1,101):
    if i**2 %3 == 0:
        list1.append(i**2)

print(list1)
"""

#Alternative way

list1=[x**2 for x in range(1,101) if x**2 %3 == 0]

print(list1)