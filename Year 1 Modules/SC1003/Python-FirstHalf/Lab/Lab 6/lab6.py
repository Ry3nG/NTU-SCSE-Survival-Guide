from sense_hat import SenseHat
from time import sleep

sense = SenseHat()

r = (255, 0, 0)  # red
g = (0, 255, 0)  # green
b = (0, 0, 0)  # blank
w = (255, 255, 255)  # white

y = 1
x = 1

game_over = False

board = [[r, r, r, r, r, r, r, r],
         [r, b, b, b, b, b, b, r],
         [r, r, r, r, r, r, b, r],
         [r, b, b, b, b, r, b, r],
         [r, b, r, g, b, r, b, r],
         [r, b, r, r, r, r, b, r],
         [r, b, b, b, b, b, b, r],
         [r, r, r, r, r, r, r, r]]


def move_marble(pitch, roll, x, y):
    new_x = x
    new_y = y

    if 1 < pitch < 179 and x != 0:
        new_x -= 1  # move left
    elif 359 > pitch > 179 and x != 7:
        new_x += 1  # move right

    if 1 < roll < 179 and y != 7:
        new_y += 1  # move up
    elif 359 > roll > 179 and y != 0:
        new_y -= 1  # move down

    new_x, new_y = check_wall(x, y, new_x, new_y)
    return new_x, new_y


def check_wall(x, y, new_x, new_y):
    if board[new_y][new_x] != r:
        return new_x, new_y

    elif board[new_y][x] != r:
        return x, new_y

    elif board[y][new_x] != r:
        return new_x, y

    else:
        return x, y


def check_gameover(game_over):
    if board[y][x] == g:
        game_over = True
    return game_over


while not game_over:
    pitch = sense.get_orientation()['pitch']
    roll = sense.get_orientation()['roll']

    x, y = move_marble(pitch, roll, x, y)
    game_over = check_gameover(game_over)

    board[y][x] = w
    sense.set_pixels(sum(board, []))
    sleep(0.03)
    board[y][x] = b

sense.clear()
sense.show_message("You Win!!")