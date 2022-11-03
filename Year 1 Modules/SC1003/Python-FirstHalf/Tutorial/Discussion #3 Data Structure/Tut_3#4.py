import math

list1 = [1,2,3,4,5,6,7,8]
list2 = [1,2,3,4,5,6,7]

if max(list1) > max(list2):
    print("Class A has the higher maximum grade" , "The maximum score is %d" %max(list1))
else:
    print("Class B has the higher maximum grade", "The maximum score is %d" %max(list2))

average_list1 = float(sum(list1)/len(list1))
average_list2 = float(sum(list2)/len(list2))

if average_list1 > average_list2:
    print("Class A has the higher average grade", "The average score is %f" %average_list1)
else:
    print("Class B has the higher average grade", "The average score is %f" %average_list2)

