"""
virtual page information:
Virtual Page 0: 0x0000 to 0x007F
Virtual Page 1: 0x0080 to 0x00FF
Virtual Page 2: 0x0100 to 0x017F
Virtual Page 3: 0x0180 to 0x01FF
Virtual Page 4: 0x0200 to 0x027F
Virtual Page 5: 0x0280 to 0x02FF
Virtual Page 6: 0x0300 to 0x037F
Virtual Page 7: 0x0380 to 0x03FF
Virtual Page 8: 0x0400 to 0x047F
Virtual Page 9: 0x0480 to 0x04FF
Virtual Page 10: 0x0500 to 0x057F
Virtual Page 11: 0x0580 to 0x05FF
Virtual Page 12: 0x0600 to 0x067F
Virtual Page 13: 0x0680 to 0x06FF
Virtual Page 14: 0x0700 to 0x077F
Virtual Page 15: 0x0780 to 0x07FF
Virtual Page 16: 0x0800 to 0x087F
Virtual Page 17: 0x0880 to 0x08FF
Virtual Page 18: 0x0900 to 0x097F
Virtual Page 19: 0x0980 to 0x09FF
Virtual Page 20: 0x0A00 to 0x0A7F
Virtual Page 21: 0x0A80 to 0x0AFF
Virtual Page 22: 0x0B00 to 0x0B7F
Virtual Page 23: 0x0B80 to 0x0BFF
Virtual Page 24: 0x0C00 to 0x0C7F
Virtual Page 25: 0x0C80 to 0x0CFF
Virtual Page 26: 0x0D00 to 0x0D7F
"""
def returnVPN(address):
    # if address in hex is within 0x0000 to 0x007F, return 0
    if address >= 0x0000 and address <= 0x007F:
        return 0
    elif address >= 0x0080 and address <= 0x00FF:
        return 1
    elif address >= 0x0100 and address <= 0x017F:
        return 2
    elif address >= 0x0180 and address <= 0x01FF:
        return 3
    elif address >= 0x0200 and address <= 0x027F:
        return 4
    elif address >= 0x0280 and address <= 0x02FF:
        return 5
    elif address >= 0x0300 and address <= 0x037F:
        return 6
    elif address >= 0x0380 and address <= 0x03FF:
        return 7
    elif address >= 0x0400 and address <= 0x047F:
        return 8
    elif address >= 0x0480 and address <= 0x04FF:
        return 9
    elif address >= 0x0500 and address <= 0x057F:
        return 10
    elif address >= 0x0580 and address <= 0x05FF:
        return 11
    elif address >= 0x0600 and address <= 0x067F:
        return 12
    elif address >= 0x0680 and address <= 0x06FF:
        return 13
    elif address >= 0x0700 and address <= 0x077F:
        return 14
    elif address >= 0x0780 and address <= 0x07FF:
        return 15
    elif address >= 0x0800 and address <= 0x087F:
        return 16
    elif address >= 0x0880 and address <= 0x08FF:
        return 17
    elif address >= 0x0900 and address <= 0x097F:
        return 18
    elif address >= 0x0980 and address <= 0x09FF:
        return 19
    elif address >= 0x0A00 and address <= 0x0A7F:
        return 20
    elif address >= 0x0A80 and address <= 0x0AFF:
        return 21
    elif address >= 0x0B00 and address <= 0x0B7F:
        return 22
    elif address >= 0x0B80 and address <= 0x0BFF:
        return 23
    elif address >= 0x0C00 and address <= 0x0C7F:
        return 24
    elif address >= 0x0C80 and address <= 0x0CFF:
        return 25
    elif address >= 0x0D00 and address <= 0x0D7F:
        return 26


# main function
if __name__ == "__main__":
    while(True):
        # get address from user
        address = int(input("Enter address in hex: "), 16)
        # get virtual page number
        vpn = returnVPN(address)
        # print virtual page number
        print("Virtual Page Number: ", vpn)