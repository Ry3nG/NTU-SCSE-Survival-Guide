###Practical Exercise 3b

max_try = 3 #maximun number of trials for erroneous input

#----------------- using while iteration & if else conditional execution -----------------------------
no_of_try = 0  #Number of trial
while no_of_try < max_try:
    no_of_try = no_of_try + 1
    red_str=input("Enter the value of the red color for message: ")
    if red_str.isdigit(): #if the string contains digits only
        msg_r_int= int(red_str) # convert it to integer
        if msg_r_int < 256:   # check whether the range is less than 256      
            break  # yes - valid input
        else:
            print("Invalid - value has to be between 0 and 255 (", no_of_try, ")")
    else:
        print("Invalid - use number only (", no_of_try, ")")
else:
    print("You have exceeded the number of trials allowed. Bye!")
    exit()

#----------------------- using for iteration & if else conditional execution --------------------------------
for no_of_try in range(max_try):
    green_str=input("Enter the value of the green color for message: ")
    if green_str.isdigit(): #if the string contains digits only
        msg_g_int= int(green_str) # convert it to integer
        if msg_g_int < 256:   # check whether the range is less than 256      
            break  # yes - valid input
        else: 
            print("Value has to be between 0 and 255 (", no_of_try+1, ")")
    else:
        print("Enter number only (", no_of_try+1, ")")
else:
    print("You have exceeded the number of trials allowed. Bye!")
    exit()

#-------------- using try and except conditional execution -------------------------
no_of_try=0
while no_of_try < max_try:
    msg_b_str=input("Enter the value of the blue color for message: ")
    try: 
        msg_b_int= int(msg_b_str) #if this return true, it means that the string contains digits only
        if 0<= msg_b_int < 256:   # further check whether the range is less than 256      
            break # yes - valid input     
        else: 
            print("Invalid - Value has to be between 0 and 255 (", no_of_try+1, ")")
    except ValueError: #false - not digits
        print("Invalid - enter number only(", no_of_try+1, ")")
    no_of_try += 1
else:
    print("You have exceeded the number of trials allowed. Bye!")
    exit()

#-------------------------------------------------------------------------------------------
msg_color= (msg_r_int,msg_g_int,msg_b_int)
print ('Message Color = ', msg_color)   #for debugging

bg_color=(0,0,0)  #default values
red_str=input("Enter the value of the red color for background: ")
green_str=input("Enter the value of the green color for background: ")
blue_str=input("Enter the value of the blue color for background: ")
bg_r_int= int(red_str)
bg_g_int= int(green_str)
bg_b_int= int(blue_str)
bg_color= (bg_r_int,bg_g_int,bg_b_int)
print("Background color = ", bg_color)   #for debugging


#-------------- using try and except conditional execution -------------------------
no_of_try=0
while no_of_try < max_try:
    no_of_try += 1
    speed_str=input("Enter the value of the display speed: ")
    try: 
        speed = float(speed_str) #if this return true, it means that the string contains floating number
        if (speed >= 0.05 and speed <= 1):   # check for valide range 
           print("Speed = ", speed)  #for debugging
           break  
        else: 
            print("Invalid - value has to be between 0.05 and 1")
    except ValueError:
        print("Invalid - enter number only")
else:
       print("You have exceeded the number of trials allowed. Bye!")
       exit()

#--------------------------------------------------------------------------------------------
