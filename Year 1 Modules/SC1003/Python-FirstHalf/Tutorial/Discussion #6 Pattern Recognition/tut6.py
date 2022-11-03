def reverser(a_str):
    if len(a_str) == 1:
        return a_str
    else:
        new_str = reverser(a_str[1:]) + a_str[0]
        return new_str


def reverseAndRepeat(a_str, num):
    if len(a_str) == 1:
        return a_str * num
    else:
        new_str = reverseAndRepeat(a_str[1:], num) + a_str[0] * num
        return new_str


def symmetricString(a_str):
    if len(a_str) == 1:
        return a_str
    else:
        new_str = a_str + reverser(a_str)
        return new_str


def main():
    myStr = "AbCdE"
    str1 = symmetricString(myStr)
    print(str1)


if __name__ == "__main__":
    main()