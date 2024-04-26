# Final Project CPSC 4420
# Author: Reeves Farrell
# Due: Tue Dec 5, 2023 11:59pm

import numpy as np
import pygame
import matplotlib.pyplot as plt

# Define trajectories and model parameters
base_trajectory = np.load("base_path.npy")
target_trajectory = np.load("ee_path.npy")

arm_length = 0.5  # 50 cm in meters
joint1_angle_range = (np.deg2rad(40), np.deg2rad(90))
joint2_angle_range = (np.deg2rad(-70), np.deg2rad(-20))

# Define state space and action space
def define_state_space():
    return np.linspace(joint1_angle_range[0], joint1_angle_range[1], 10), \
           np.linspace(joint2_angle_range[0], joint2_angle_range[1], 10)

def define_action_space():
    return np.array([-np.deg2rad(5), 0, np.deg2rad(5)])

state_space = define_state_space()
action_space = define_action_space()

# Define dynamics and reward functions
def forward_kinematics(joint_angles):
    q1, q2 = joint_angles
    x = arm_length * (np.cos(q1) + np.cos(q1 + q2))
    y = arm_length * (np.sin(q1) + np.sin(q1 + q2))
    return x, y

def transition_model(state, action):
    new_state = np.array(state) + np.array(action)
    new_state[0] = np.clip(new_state[0], joint1_angle_range[0], joint1_angle_range[1])
    new_state[1] = np.clip(new_state[1], joint2_angle_range[0], joint2_angle_range[1])
    return tuple(new_state)

def reward_function(current_state, target_state):
    current_position = forward_kinematics(current_state)
    target_position = forward_kinematics(target_state)
    return -np.linalg.norm(np.array(current_position) - np.array(target_position))

# Initialize Q-learning parameters
q_table = np.zeros((len(state_space[0]), len(state_space[1]), len(action_space)))
learning_rate = 0.1
discount_factor = 0.9
exploration_prob = 0.2
num_episodes = 1000

# Corrected state_to_index function
def state_to_index(state):
    joint1_index = np.argmin(np.abs(state_space[0] - state[0]))
    joint2_index = np.argmin(np.abs(state_space[1] - state[1]))
    return joint1_index, joint2_index

# Update the Q-learning loop and any other place where q_table is accessed
# Use state_to_index to convert the state to valid indices for the Q-table
for episode in range(num_episodes):
    state = (state_space[0][0], state_space[1][0])  # Starting state
    state_index = state_to_index(state)

    for step in range(100):
        if np.random.rand() < exploration_prob:
            action_index = np.random.choice(len(action_space))
        else:
            action_index = np.argmax(q_table[state_index])

        action = action_space[action_index]
        next_state = transition_model(state, action)
        next_state_index = state_to_index(next_state)

        # Rest of the Q-learning update logic...
        state = next_state
        state_index = next_state_index

# Pygame visualization
WINDOW_WIDTH, WINDOW_HEIGHT = 800, 600
pygame.init()
screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption('UAV Trajectory Visualization')

WHITE = (255, 255, 255)
RED = (255, 0, 0)
BLUE = (0, 0, 255)

def draw_uav(position):
    pygame.draw.circle(screen, RED, position, 5)

# Correct the calculate_position function
def calculate_position(state):
    state_index = state_to_index(state)
    joint_angles = (state_space[0][state_index[0]], state_space[1][state_index[1]])
    position = forward_kinematics(joint_angles)
    # Convert the position to Pygame coordinates
    x = int(WINDOW_WIDTH / 2 + position[0] * 100)
    y = int(WINDOW_HEIGHT / 2 - position[1] * 100)
    return (x, y)

# Ensure visualize_results uses the correct state indexing
def visualize_results(q_table):
    running = True
    clock = pygame.time.Clock()
    state = (state_space[0][0], state_space[1][0])  # Starting state
    state_index = state_to_index(state)

    while running:
        # Event handling and screen filling
        position = calculate_position(state)
        draw_uav(position)
        # Update display and state
        action_index = np.argmax(q_table[state_index])
        action = action_space[action_index]
        state = transition_model(state, action)
        state_index = state_to_index(state)
        clock.tick(60)

    pygame.quit()

# Call visualize_results with the updated q_table
visualize_results(q_table)