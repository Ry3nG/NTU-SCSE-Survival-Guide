def bubbleSort(myList):
    for passNum in range(len(myList) - 1):
        swapped = False
        for i in range(len(myList) - 1):
            if myList[i] > myList[i + 1]:
                myList[i], myList[i + 1] = myList[i + 1], myList[i]
                swapped = True
        if not swapped:
            break
    return myList


myList = [9, 8, 7, 6, 5, 4, 3, 2, 1]

print(bubbleSort(myList))