import math
from random import randint

bulls = 0
cows = 0
num = str(randint(1000, 9999))
#num = ("0536")
list1 = list(num)
list2 = []


def testBulls(list1, list2):
    bulls = 0
    if list1[0] == list2[0]:
        bulls = bulls + 1
    if list1[1] == list2[1]:
        bulls = bulls + 1
    if list1[2] == list2[2]:
        bulls = bulls + 1
    if list1[3] == list2[3]:
        bulls = bulls + 1
    return bulls


def testCows(list1, list2):
    cows = 0
    if list2[0] in list1 and list2[0] != list1[0]:
        cows = cows + 1
    if list2[1] in list1 and list2[1] != list1[1]:
        cows = cows + 1
    if list2[2] in list1 and list2[2] != list1[2]:
        cows = cows + 1
    if list2[3] in list1 and list2[3] != list1[3]:
        cows = cows + 1
    return cows


#mainprogram
while bulls < 4:
    guess = input("Please input 4 digits: ")
    list2 = list(guess)
    bulls = testBulls(list1, list2)
    cows = testCows(list1, list2)
    if bulls == 4:
        continue
    print(bulls, "A(Bulls)", cows, "B(Cows)")
else:
    print("You win!!")


