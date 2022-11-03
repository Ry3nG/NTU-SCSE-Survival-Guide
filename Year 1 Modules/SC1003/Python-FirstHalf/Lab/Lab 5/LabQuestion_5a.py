from sense_hat import SenseHat
sense = SenseHat()
sense.set_rotation(180)

def get_colour(colour):
    keep_looping = True
    no_of_try = 1

    while no_of_try < 3:
        no_of_try = no_of_try + 1
        colour_str = input("Enter the value of the "+ colour +"colour for message (0 to 255)") 
        if colour_str.isdigit(): #if the string contains digits only
            colour_int= int(colour_str)
            if colour_int < 256:   # check whether the range is less than 256
                break
            else:
                print("Invalid - value has to be between 0 and 255 (", no_of_try, ")")
        else:
            print("Invalid - use number only (", no_of_try, ")")
    else:
        return 0

    return colour_int

#---------------------------------------
def main():
    r_int = get_colour("Red")
    g_int = get_colour("Green")
    b_int = get_colour("Blue")

    msg_colour = (r_int, g_int, b_int)

    sense.show_message("I got it!", text_colour = msg_colour)



if __name__ == "__main__":
    main()