from sense_hat import SenseHat
from LabQuestion_5a import get_colour

sense = SenseHat()
sense.set_rotation(180)


r_int = get_colour("Red")
g_int = get_colour("Green")
b_int = get_colour("Blue")

msg_colour = (r_int, g_int, b_int)

sense.show_message("I got it!", text_colour = msg_colour)