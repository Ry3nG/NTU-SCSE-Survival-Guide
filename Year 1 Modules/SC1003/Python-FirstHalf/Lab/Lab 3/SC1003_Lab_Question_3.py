#importing libray
import math
#from sense_hat import SenseHat
#sense = SenseHat()

#configuration
R_msg_valid = False
G_msg_valid = False
B_msg_valid = False

R_bg_valid = False
G_bg_valid = False
B_bg_valid = False

speed_valid = False

max_trial = 3
trial = 0

#main body

while not R_msg_valid:
    try:
        R_msg = int(
            input("Enter the value of the red colour for the message: "))
        while (R_msg < 0 or R_msg > 255):
            trial = trial + 1
            print("The value must be in between 0~255! Please re-input.")
            R_msg = int(
                input(
                    "Enter the value of the red colour for the message: "))
        else:
            R_msg_valid = True
    except:
        print("Invalid input! Please input an integer!")
        trial = trial + 1

while not G_msg_valid:
        try:
            G_msg = int(
                input("Enter the value of the green colour for the message: "))
            while (G_msg < 0 or G_msg > 255):
                trial = trial + 1
                print("The value must be in between 0~255! Please re-input.")
                G_msg = int(
                    input(
                        "Enter the value of the green colour for the message: "
                    ))
            else:
                G_msg_valid = True
        except:
            print("Invalid input! Please input an integer!")
            trial = trial + 1

while not B_msg_valid:
        try:
            B_msg = int(
                input("Enter the value of the blue colour for the message: "))
            while (B_msg < 0 or B_msg > 255):
                trial = trial + 1
                print("The value must be in between 0~255! Please re-input.")
                B_msg = int(
                    input(
                        "Enter the value of the blue colour for the message: ")
                )
            else:
                B_msg_valid = True
        except:
            print("Invalid input! Please input an integer!")
            trial = trial + 1

while not R_bg_valid:
        try:
            R_bg = int(
                input(
                    "Enter the value of the red colour for the background: "))
            while (R_bg < 0 or R_bg > 255):
                trial = trial + 1
                print("The value must be in between 0~255! Please re-input.")
                R_bg = int(
                    input(
                        "Enter the value of the red colour for the background: "
                    ))
            else:
                R_bg_valid = True
        except:
            print("Invalid input! Please input an integer!")
            trial = trial + 1

while not G_bg_valid:
        try:
            G_bg = int(
                input(
                    "Enter the value of the green colour for the background: ")
            )
            while (G_bg < 0 or G_bg > 255):
                trial = trial + 1
                print("The value must be in between 0~255! Please re-input.")
                G_bg = int(
                    input(
                        "Enter the value of the green colour for the background: "
                    ))
            else:
                G_bg_valid = True
        except:
            print("Invalid input! Please input an integer!")
            trial = trial + 1

while not B_bg_valid:
        try:
            B_bg = int(
                input(
                    "Enter the value of the blue colour for the background: "))
            while (B_bg < 0 or B_bg > 255):
                trial = trial + 1
                print("The value must be in between 0~255! Please re-input.")
                B_bg = int(
                    input(
                        "Enter the value of the blue colour for the background: "
                    ))
            else:
                B_bg_valid = True
        except:
            print("Invalid input! Please input an integer!")
            trial = trial + 1

while not speed_valid:
        try:
            speed = float(input("Enter the scroll speed you desire: "))
            while (speed < 0 or speed > 1):
                trial = trial + 1
                print("The value must be in between 0~1! Please re-input.")
                speed = float(input("Enter the scroll speed you desire: "))
            else:
                speed_valid = True
        except:
            print("Invalid input! Please input a float!")
            trial = trial + 1
#if 0 <= R_msg <= 255 and 0 <= G_msg <= 255 and 0 <= B_msg <= 255 and 0 <= R_bg <= 255 and 0 <= G_bg <= 255 and 0 <= B_bg <= 255 and 0 <= speed <= 1:

#outputing
colour_msg = (R_msg, G_msg, B_msg)
colour_bg = (R_bg, G_bg, B_bg)
print("You inputted all required value, you message RGB is:", colour_msg,
      "your background RGB is", colour_bg, "your scroll speed is", speed)
print("Your message is processing...")

#sense,set_rotation(180)
#sense.show_message("Successful!" , text_colour = colour_msg , back_colour = colour_bg , scroll_speed = speed)

#sense.clear()
