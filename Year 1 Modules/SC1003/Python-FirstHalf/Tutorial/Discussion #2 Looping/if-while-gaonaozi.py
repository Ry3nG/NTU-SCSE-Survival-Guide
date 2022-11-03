import math

value = 6
if value % 2 == 0:
    print("first" , value)
elif value % 3 == 0:
    print("second" , value)

while value <=9:
    value = value + 1
    if value ==8:
        continue
    else:
        pass
    print("third" , value)
else:
    print("fourth" , value)

print("fifth", value)




