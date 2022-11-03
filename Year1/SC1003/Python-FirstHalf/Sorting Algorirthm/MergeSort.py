my_list = [9, 8, 7, 6, 5, 4, 3, 2, 1]


def mergeSort(my_list):
    listLength = len(my_list)

    # base case
    if listLength < 2:
        return my_list
    left_list = my_list[:listLength // 2]
    right_list = my_list[listLength // 2:]

    # merge sort left and right recursively
    left_list = mergeSort(left_list)
    right_list = mergeSort(right_list)
    return merge(left_list, right_list)


def merge(left_list, right_list):
    result_list = []

    # while left and right list has elements
    while left_list and right_list:
        if left_list[0] < right_list[0]:
            result_list.append(left_list[0])
            left_list.pop(0)
        else:
            result_list.append(right_list[0])
            right_list.pop(0)

    # left list still contain elements. Append its contents to end of the result
    if left_list:
        result_list.extend(left_list)
    else:
        # right list still contain elements. Append its contents to end of the result
        result_list.extend(right_list)

    return result_list

print(mergeSort(my_list))