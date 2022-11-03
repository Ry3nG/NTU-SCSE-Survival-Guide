import math

num_boy = int(input("Enter the number of boys: "))
num_girl = int(input("Enter the number of girls: "))

rate_boy = (num_boy / (num_boy + num_girl)) * 100
rate_girl = (num_girl / (num_boy + num_girl)) * 100

print("Boys:"  , round(rate_boy),  "%" , sep="" )
print("Girls:" , round(rate_girl), "%" , sep="")