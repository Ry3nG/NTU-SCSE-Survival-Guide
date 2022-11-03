# Tutorial Discussion #5

### Step 1

> To play the 1A2B game, what are the steps (procedures) needed? What is the flow of them? Come up with your design (algorithm) by pseudocode/flowchart first.

Pseudocode:

1. Generate the target number
2. Get the number guessing from users
3. compare the user guessing with the target
4. if the user guessing is not correct, goto step 2
5. if the user guessing hits, termiate the game

```python
import libraries
from random import randint
Bulls = 0
Cows = 0

num = str(randint(1000,9999))
list1 = list(num)

guess = input("Enter your guess: ")
list2 = list(guess)

testBulls()

testCows()

Print result

```
