my_list = [9,8,7,6,5,4,3,2,1]


def bubbleSort(my_list):
    count = 0
    num = len(my_list)
    while count < (num - 1)**2:
        for i in range(num - 1):
            if my_list[i] > my_list[i + 1]:
                my_list[i], my_list[i + 1] = my_list[i + 1], my_list[i]
                count += 1
            else:
                count += 1
    return my_list


print(bubbleSort(my_list))
