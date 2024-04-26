# Assignment 2 CPSC 4420
# Author: Reeves Farrell
# Due: SEP 26, 2023 @11:59 PM

import numpy as np
import math

# Grid size
grid_size = 5  

# Actions 
forward_1 = 0
forward_2 = 1
turn_left = 2
turn_right = 3

# Direction values
up = 0 
down = 1
left = 2
right = 3

# Rewards
green = 100
red = -1000   

# Action costs
action_costs = [1, 1.5, 0.5, 0.5]  

# Blocked cells
blocked_cells = [(1,2), (4,1), (4,3)]

# Initial V value
V = {}

for i in range(grid_size):
    for j in range(grid_size):
        for d in range(4):
            V[(i,j,d)] = 0
            
V[(0,0, up)] = 0 
V[(4,4, down)] = green
V[(3,1, down)] = red

def possible_actions(state):
    x, y, d = state

    actions = [forward_1, turn_left, turn_right]
    
    if d == up and (x, y - 2, d) not in blocked_cells:
        actions.append(forward_2)
    elif d == down and (x, y + 2, d) not in blocked_cells:
        actions.append(forward_2)
    elif d == left and (x - 2, y, d) not in blocked_cells:
        actions.append(forward_2)
    elif d == right and (x + 2, y, d) not in blocked_cells:
        actions.append(forward_2)
        
    return actions

def execute_action(state, action):
    x, y, d = state
    
    if action == forward_1:
        if d == up:
            next_state = (x, y - 1, d)
        elif d == down:
            next_state = (x, y + 1, d)
        elif d == left:
            next_state = (x - 1, y, d)
        elif d == right: 
            next_state = (x + 1, y, d)
    elif action == forward_2:
        if d == up:
            next_state = (x, y - 2, d)
        elif d == down:
            next_state = (x, y + 2, d) 
        elif d == left:
            next_state = (x - 2, y, d)
        elif d == right:
            next_state = (x + 2, y, d)
    elif action == turn_left:
        if d == up:
            next_state = (x, y, left)
        elif d == down:
            next_state = (x, y, right)
        elif d == left:
            next_state = (x, y, down)
        elif d == right:
            next_state = (x, y, up)
    elif action == turn_right:
        if d == up:
            next_state = (x, y, right) 
        elif d == down:
            next_state = (x, y, left)
        elif d == left:
            next_state = (x, y, up)
        elif d == right:
            next_state = (x, y, down)
    
    # Checks for out of bounds
    if next_state[0] < 0 or next_state[0] >= grid_size:
        return state
    if next_state[1] < 0 or next_state[1] >= grid_size:
        return state
    if next_state in blocked_cells:
        return state
        
    return next_state

def value_iteration(V, gamma, num_iterations):
    for i in range(num_iterations):
        print("iter", i + 1, end="")
        print(':')
        
        delta = 0

        for state in V:
            v = V[state]
            
            best_value = float('-inf')
            best_action = None
            
            for action in possible_actions(state):
                next_state = execute_action(state, action)
                next_value = V[next_state]
                action_value = -action_costs[action] + gamma * next_value
                
                if action_value > best_value:
                    best_value = action_value
                    best_action = action
                    
            delta = max(delta, np.abs(v - best_value))
            
            V[state] = best_value

            print("state", state, "  V =", V[state], "  Best action:", best_action)
            
        if delta < 0:
            break

        print()
            
    return V

# Adjust gamma per problem
gamma = 1.0
num_iterations = 10

V = value_iteration(V, gamma, num_iterations)