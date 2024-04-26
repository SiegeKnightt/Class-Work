import time
import pygame
import numpy as np

# Define the grid world
grid = [
    ['S', ' ', ' ', ' ', ' ', ' '],
    ['X', 'X', ' ', 'X', ' ', ' '],
    ['X', ' ', 'A', 'X', 'A', 'X'],
    ['X', ' ', 'X', ' ', ' ', ' '],
    ['X', ' ', 'B', ' ', 'X', 'C'],
    ['X', ' ', 'X', ' ', ' ', 'T'],
]

# Define the rewards for each state
rewards = {
    'S': 0,
    'X': -1,
    'T': 5,
    'A': -1,
    'B': -2,
    'C': -5,
    ' ': 0,  # Default reward for empty cells
}

# Define the possible actions
actions = ['up', 'down', 'left', 'right']

# Define parameters for value iteration. You can change those parameters as needed
gamma = 0.9  # Discount factor
epsilon = 0.01  # Convergence threshold

# Initialize the pygame window and display the grid world
pygame.init()
screen = pygame.display.set_mode((600, 600))
pygame.display.set_caption("Grid World MDP")

def draw_grid():
    screen.fill((255, 255, 255))
    cell_size = 100

    for row in range(len(grid)):
        for col in range(len(grid[0])):
            pygame.draw.rect(screen, (0, 0, 0), (col * cell_size, row * cell_size, cell_size, cell_size), 1)
            cell_center = (col * cell_size + cell_size // 2, row * cell_size + cell_size // 2)

            if grid[row][col] == 'S':
                pygame.draw.circle(screen, (0, 255, 0), cell_center, cell_size // 3)
            elif grid[row][col] == 'X':
                pygame.draw.rect(screen, (255, 0, 0), (col * cell_size, row * cell_size, cell_size, cell_size))
            elif grid[row][col] == 'T':
                pygame.draw.circle(screen, (0, 0, 255), cell_center, cell_size // 3)
            elif grid[row][col] in ['A', 'B', 'C']:
                # Draw rewards
                font = pygame.font.SysFont("monospace", 36)
                text = font.render(str(rewards[grid[row][col]]), True, (0, 0, 0))
                screen.blit(text, (col * cell_size + cell_size // 2 - text.get_width() // 2, row * cell_size + cell_size // 2 - text.get_height() // 2))

    pygame.display.flip()
### Value Iteration
def value_iteration():
    # Initialize value function and best actions
    value_function = np.zeros((len(grid), len(grid[0])))
    best_actions = [[' ' for _ in range(len(grid[0]))] for _ in range(len(grid))]

    all_value_functions = [np.copy(value_function)]  # Store all value functions
    all_best_actions = [np.copy(best_actions)]  # Store all best actions

    while True:
        delta = 0
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] not in ['X', 'T']:
                    v = value_function[row][col]
                    best_action = None
                    best_value = float('-inf') # Initialize the best value function
                    noise = 0.3
                    for action in actions:
                        new_row, new_col = row, col  # Initialize with the current state
                        if action == 'up':
                            new_row = max(row - 1, 0)
                        elif action == 'down':
                            new_row = min(row + 1, len(grid) - 1)
                        elif action == 'left':
                            new_col = max(col - 1, 0)
                        elif action == 'right':
                            new_col = min(col + 1, len(grid[0]) - 1)

                        if grid[new_row][new_col] != 'X':
                            value = rewards.get(grid[new_row][new_col], 0) + gamma * value_function[new_row][new_col]
                            value = value * (1 - noise)
                            for a in actions:
                                if a != action:
                                    value += 0.1 * gamma * value_function[new_row][new_col]
                            if value > best_value:
                                best_value = value
                                best_action = action

                    value_function[row][col] = best_value
                    best_actions[row][col] = best_action
                    delta = max(delta, abs(v - best_value))

        all_value_functions.append(np.copy(value_function))
        all_best_actions.append(np.copy(best_actions))

        if delta < epsilon:
            break

    return value_function, best_actions, all_value_functions, all_best_actions

def visualize_value_iteration(all_value_functions,all_best_actions):
    cell_size = 100
    max_iterations = 100 


    for iteration in range(min(max_iterations, len(all_value_functions))):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return

        screen.fill((255, 255, 255))
        draw_grid()

        # Display the current value estimates
        value_function = all_value_functions[iteration]
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] not in ['S', 'X', 'T']:
                    font = pygame.font.Font(None, 36)
                    text = font.render(f'{value_function[row][col]:.2f}', True, (0, 0, 0))
                    screen.blit(text, (col * cell_size + cell_size // 2 - text.get_width() // 2, row * cell_size + cell_size // 2 - text.get_height() // 2))

        pygame.display.flip()
        time.sleep(1.0)
        

def draw_policy(value_function, best_actions):
    cell_size = 100

    for row in range(len(grid)):
        for col in range(len(grid[0])):
            if grid[row][col] not in ['S', 'X', 'T']:
                best_action = best_actions[row][col]

                font = pygame.font.Font(None, 36)
                text = font.render(best_action, True, (0, 0, 0))
                screen.blit(text, (col * cell_size + cell_size // 2 - text.get_width() // 2, row * cell_size + cell_size // 2 - text.get_height() // 2))

    pygame.display.flip()


    


def traverse_optimal_path(value_function, best_actions):
    current_state = (0, 0)
    cell_size = 100

    while grid[current_state[0]][current_state[1]] != 'T':
        row, col = current_state
        best_action = best_actions[row][col]

        new_state = current_state  # Initialize new_state

        for action in actions:
            if best_action == 'up':
                new_state = max(row - 1, 0), col
            elif best_action == 'down':
                new_state = min(row + 1, len(grid) - 1), col
            elif best_action == 'left':
                new_state = row, max(col - 1, 0)
            elif best_action == 'right':
                new_state = row, min(col + 1, len(grid[0]) - 1)

        # Update the Pygame window to show the agent's movement
        screen.fill((255, 255, 255))
        draw_grid()
        pygame.draw.circle(screen, (255, 255, 0), (current_state[1] * cell_size + cell_size // 2, current_state[0] * cell_size + cell_size // 2), cell_size // 3)
        pygame.display.flip()

        time.sleep(0.2)

        # Update the current state after all actions have been considered
        current_state = new_state  # Move this line here, after the loop ends


def main():
    draw_grid()
    pygame.display.flip()
    value_function, best_actions, all_value_functions,all_best_actions = value_iteration()  # Run Value Iteration
    com = input('v: for value iteration,a: for action list, t: for optimal trajectory')    
    while True:
        if com == 'v':
            visualize_value_iteration(all_value_functions, all_best_actions)
        elif com == 't':
            traverse_optimal_path(value_function, best_actions)
        elif com == 'a':
            draw_policy(value_function, best_actions)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return  # Exit the main function
if __name__ == "__main__":
    main()

