# Assignment 1 CPSC 4420/6420
# Author: Reeves Farrell
# Due: SEP 14, 2023 @04:59 PM

from itertools import permutations
from collections import deque
import random
import time
import copy
import heapq

# Starting state for A and B
start = [7,2,4,5,0,6,8,3,1]

# Prints the state
def print_state(state):
    for x in state:
        print(x, end="")
    print()

# Part A
def part_A():  
    print("Part A:")
    print()

    states = list(permutations(start))

    random.shuffle(states)

    for i in range(5):
        print_state(states[i])
   
# Part B
def part_B():
    print("Part B:")
    print()

    states = list(permutations(start))

    random.shuffle(states)

    def odd_neighbors(state):
        for i in range(len(state)):
            if state[i] % 2 != 0:
                if (i > 0 and state[i - 1] % 2 != 0) or (i < len(state) - 1 and state[i + 1] % 2 != 0):
                    return False
                elif (i > 0 and state[i - 3] % 2 != 0) or (i < len(state) - 3 and state[i + 1] % 2 != 0):
                    return False
        return True

    valid_states = [state for state in states if odd_neighbors(state)]

    random.shuffle(valid_states)

    for i in range(10):
        print_state(valid_states[i])

# Part C
def part_C():
    print("Part C:")
    print()

    state = ""

    while len(state) != 9:
        state = input("Please enter a 9 digit state:\n")

    state = list(state)
    print()

    # 1 = Up
    # 2 = Down
    # 3 = Left
    # 4 = Right
    move = int(input("Please enter 1 for up, 2 for down, 3 for left, or 4 for right:\n"))
    print()

    for i in range(len(state)):
        if int(state[i]) == 0:
            if move == 1:
                # move up
                if i < 3:
                    print("Cannot move up")
                    print()
                    break
                else:
                    temp = state[i]
                    state[i] = state[i - 3]
                    state[i - 3] = temp
                    break
            elif move == 2:
                # move down
                if i > 5:
                    print("Cannot move down")
                    print()
                    break
                else:
                    temp = state[i]
                    state[i] = state[i + 3]
                    state[i + 3] = temp
                    break
            elif move == 3:
                # move left
                if i == 0 or i == 3 or i == 6:
                    print("Cannot move left")
                    print()
                    break
                else:
                    temp = state[i]
                    state[i] = state[i - 1]
                    state[i - 1] = temp
                    break
            elif move == 4:
                # move right
                if i == 8 or i == 5 or i == 2:
                    print("Cannot move right")
                    print()
                    break
                else:
                    temp = state[i]
                    state[i] = state[i + 1]
                    state[i + 1] = temp
                    break

    print("Output State:")
    print_state(state)

# Part D
# Due to the random actions,
# this part of the assignment
# can either be quick or long.
# I have tested this multiple
# times and have had it work
# in under 30 seconds and
# have had it go for over 30 minutes.
def part_D():
    print("Part D:")
    print()

    # Goal state where each row is divisible by 3
    goal = ['7','2','0','5','4','6','8','3','1']
    goal = list(goal)

    state = ""

    while len(state) != 9:
        state = input("Please enter a 9 digit state:\n")

    state = list(state)

    if state == goal:
        return

    while state != goal:
        move = random.randint(1,4)
        print(f"Random Move: {move}")
        #time.sleep(1)
        for i in range(9):
            if int(state[i]) == 0:
                if move == 1:
                    # move up
                    if i < 3:
                        print("Cannot move up")
                        break
                    else:
                        temp = state[i]
                        state[i] = state[i - 3]
                        state[i - 3] = temp
                        print("Move: Up")
                        break
                elif move == 2:
                    # move down
                    if i > 5:
                        print("Cannot move down")
                        break
                    else:
                        temp = state[i]
                        state[i] = state[i + 3]
                        state[i + 3] = temp
                        print("Move: Down")
                        break
                elif move == 3:
                    # move left
                    if i == 0 or i == 3 or i == 6:
                        print("Cannot move left")
                        break
                    else:
                        temp = state[i]
                        state[i] = state[i - 1]
                        state[i - 1] = temp
                        print("Move: Left")
                        break
                elif move == 4:
                    # move right
                    if i == 8 or i == 5 or i == 2:
                        print("Cannot move right")
                        break
                    else:
                        temp = state[i]
                        state[i] = state[i + 1]
                        state[i + 1] = temp
                        print("Move: Right")
                        break
        #time.sleep(1)
        print_state(state)
        #time.sleep(1)

    print("Goal State Achieved:")
    print_state(state)

# Part E
def part_E():
    print("Part E:")
    print()

    goal = ['0','1','2','3','4','5','6','7','8']
    start = ['3','1','2','0','7','5','4','6','8']

    moves = [1,2,3,4]
    
    def next_boards(board):
        next_states = []
        blank = board.index('0')

        for move in moves:
            board_copy = copy.deepcopy(board)
            if move == 1 and blank > 2:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank - 3]
                board_copy[blank - 3] = temp
                next_states.append((board_copy, 'Up'))
            elif move == 2 and blank < 6:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank + 3]
                board_copy[blank + 3] = temp
                next_states.append((board_copy, 'Down'))
            elif move == 3 and blank % 3 != 0:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank - 1]
                board_copy[blank - 1] = temp
                next_states.append((board_copy, 'Left'))
            elif move == 4 and blank % 3 != 2:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank + 1]
                board_copy[blank + 1] = temp
                next_states.append((board_copy, 'Right'))
                    
        return next_states

    queue = []
    queue.append((start, []))

    visited = set()

    while queue:
        current_state, taken_moves = queue.pop(0)
        #print(current_state)
        if current_state == goal:
            print("Starting State:")
            print_state(start)
            print("Goal State Achieved:")
            print_state(current_state)
            print("Moves:")
            for move in taken_moves:
                print(move)
            break
        elif tuple(current_state) not in visited:
            next_states = next_boards(current_state)

            for next_state, move in next_states:
                queue.append((next_state, taken_moves + [move]))

            visited.add(tuple(current_state))

# Part F
def part_F():
    print("Part F:")
    print()

    goal = ['0', '1', '2', '3', '4', '5', '6', '7', '8']
    start = ['3', '1', '2', '4', '0', '5', '6', '7', '8']
    
    moves = [1, 2, 3, 4]

    def next_boards(board):
        next_states = []
        blank = board.index('0')

        for move in moves:
            board_copy = copy.deepcopy(board)
            if move == 1 and blank > 2:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank - 3]
                board_copy[blank - 3] = temp
                next_states.append((board_copy, 'Up'))
            elif move == 2 and blank < 6:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank + 3]
                board_copy[blank + 3] = temp
                next_states.append((board_copy, 'Down'))
            elif move == 3 and blank % 3 != 0:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank - 1]
                board_copy[blank - 1] = temp
                next_states.append((board_copy, 'Left'))
            elif move == 4 and blank % 3 != 2:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank + 1]
                board_copy[blank + 1] = temp
                next_states.append((board_copy, 'Right'))

        return next_states

    stack = []
    stack.append((start, []))

    visited = set()

    while stack:
        current_state, taken_moves = stack.pop()
        # print(current_state)
        if current_state == goal:
            print("Starting State:")
            print_state(start)
            print("Goal State Achieved:")
            print_state(current_state)
            print("Moves:")
            for move in taken_moves:
                print(move)
            break
        elif tuple(current_state) not in visited:
            next_states = next_boards(current_state)

            for next_state, move in next_states:
                stack.append((next_state, taken_moves + [move]))

            visited.add(tuple(current_state))

# Part G
def part_G():
    print("Part G:")
    print()

    goal = ['1','2','3','8','0','4','7','6','5']
    start = ['2','3','4','1','6','0','8','7','5']

    moves = [1,2,3,4]
    
    def next_boards(board):
        next_states = []
        blank = board.index('0')

        for move in moves:
            board_copy = copy.deepcopy(board)
            if move == 1 and blank > 2:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank - 3]
                board_copy[blank - 3] = temp
                next_states.append((board_copy, 'Up'))
            elif move == 2 and blank < 6:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank + 3]
                board_copy[blank + 3] = temp
                next_states.append((board_copy, 'Down'))
            elif move == 3 and blank % 3 != 0:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank - 1]
                board_copy[blank - 1] = temp
                next_states.append((board_copy, 'Left'))
            elif move == 4 and blank % 3 != 2:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank + 1]
                board_copy[blank + 1] = temp
                next_states.append((board_copy, 'Right'))
                    
        return next_states

    queue = []
    queue.append((start, []))

    visited = set()

    while queue:
        current_state, taken_moves = queue.pop(0)
        if current_state == goal:
            print("Starting State:")
            print_state(start)
            print("Goal State Achieved:")
            print_state(current_state)
            print("Moves:")
            for move in taken_moves:
                print(move)
            break
        elif tuple(current_state) not in visited:
            next_states = next_boards(current_state)

            for next_state, move in next_states:
                queue.append((next_state, taken_moves + [move]))

            visited.add(tuple(current_state))

# Part H
def part_H():
    print("Part H:")
    print()

    goal = ['0', '1', '2', '3', '4', '5', '6', '7', '8']
    start = ['3', '0', '1', '4', '5', '2', '6', '7', '8']

    question = input("Press 1 for equal moves(G1) or 2 for unique move costs(G2):")
    
    if question == '1':
        move_costs = {
            'Up': 1,
            'Down': 1,
            'Left': 1,
            'Right': 1,
        }
    elif question == '2':
        move_costs = {
            'Up': 1.5,
            'Down': 0.5,
            'Left': 1,
            'Right': 2,
        }
    else:
        move_costs = {
            'Up': 1,
            'Down': 1,
            'Left': 1,
            'Right': 1,
        }


    def next_boards(board, move_costs):
        next_states = []
        blank = board.index('0')

        for move, cost in move_costs.items():
            board_copy = copy.deepcopy(board)
            if move == 'Up' and blank > 2:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank - 3]
                board_copy[blank - 3] = temp
                next_states.append((board_copy, 'Up', cost))
            elif move == 'Down' and blank < 6:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank + 3]
                board_copy[blank + 3] = temp
                next_states.append((board_copy, 'Down', cost))
            elif move == 'Left' and blank % 3 != 0:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank - 1]
                board_copy[blank - 1] = temp
                next_states.append((board_copy, 'Left', cost))
            elif move == 'Right' and blank % 3 != 2:
                temp = board_copy[blank]
                board_copy[blank] = board_copy[blank + 1]
                board_copy[blank + 1] = temp
                next_states.append((board_copy, 'Right', cost))

        return next_states

    def uniform_cost_search(move_costs):
        ucs = [(0, start, [])]
        visited = set()

        while ucs:
            current_cost, current_state, moves = heapq.heappop(ucs)

            if current_state == goal:
                print("Starting State:")
                print_state(start)
                print("Goal State Achieved:")
                print_state(current_state)
                print("Moves:")
                total_cost = current_cost
                for move, move_cost in moves:
                    print(f"{move} (Cost: {move_cost})")
                print(f"Total Cost: {total_cost}")
                break

            if tuple(current_state) in visited:
                continue

            visited.add(tuple(current_state))

            next_states = next_boards(current_state, move_costs)

            for next_state, move, cost in next_states:
                if tuple(next_state) not in visited:
                    next_moves = moves + [(move, cost)]
                    heapq.heappush(ucs, (current_cost + cost, next_state, next_moves))

    uniform_cost_search(move_costs)

# Main Options
run = True

while run:
    print("Select an option:")
    print("A: Part A")
    print("B: Part B")
    print("C: Part C")
    print("D: Part D")
    print("E: Part E")
    print("F: Part F")
    print("G: Part G")
    print("H: Part H")
    print("Q: Quit")
    option = input()

    if option == "A" or option == "a":
        part_A()
    elif option == "B" or option == "b":
        part_B()
    elif option == "C" or option == "c":
        part_C()
    elif option == "D" or option == "d":
        part_D()
    elif option == "E" or option == "e":
        part_E()
    elif option == "F" or option == "f":
        part_F()
    elif option == "G" or option == "g":
        part_G()
    elif option == "H" or option == "h":
        part_H()
    elif option == "Q" or option == "q":
        run = False
    else:
        print("Invalid Selection")