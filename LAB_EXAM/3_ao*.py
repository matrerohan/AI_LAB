import heapq
import numpy as np

# Define the goal state
goal_state = np.array([[1, 2, 3],
                        [4, 5, 6],
                        [7, 8, 0]])

# Define the possible moves
moves = [(0, 1), (0, -1), (1, 0), (-1, 0)]

# Define a class to represent a state in the puzzle
class State:
    def __init__(self, board, moves=0, prev=None):
        self.board = board
        self.moves = moves
        self.prev = prev
        self.cost = self.calculate_cost()

    def calculate_cost(self):
        return self.moves + self.calculate_heuristic()

    def calculate_heuristic(self):
        return np.sum(self.board != goal_state)

    def __lt__(self, other):
        return self.cost < other.cost

    def __eq__(self, other):
        return np.array_equal(self.board, other.board)

    def get_neighbors(self):
        neighbors = []
        zero_row, zero_col = np.where(self.board == 0)
        for move in moves:
            new_row, new_col = zero_row[0] + move[0], zero_col[0] + move[1]
            if 0 <= new_row < 3 and 0 <= new_col < 3:
                new_board = self.board.copy()
                new_board[zero_row, zero_col], new_board[new_row, new_col] = new_board[new_row, new_col], new_board[zero_row, zero_col]
                neighbors.append(State(new_board, self.moves + 1, self))
        return neighbors

    def get_path(self):
        path = []
        current = self
        while current:
            path.append(current.board)
            current = current.prev
        return list(reversed(path))

# Define the AO* algorithm to solve the puzzle
def solve_puzzle(initial_state):
    heap = [initial_state]
    heapq.heapify(heap)
    visited = set()
    while heap:
        current = heapq.heappop(heap)
        if np.array_equal(current.board, goal_state):
            return current.get_path()
        visited.add(tuple(map(tuple, current.board)))
        for neighbor in current.get_neighbors():
            if tuple(map(tuple, neighbor.board)) not in visited:
                heapq.heappush(heap, neighbor)
    return None

# Get the initial state from the user
initial_state = np.zeros((3, 3), dtype=int)
print("Enter the initial state (use 0 to represent the blank space):")
for i in range(3):
    initial_state[i] = list(map(int, input().split()))

initial_state = State(initial_state)

# Solve the puzzle
path = solve_puzzle(initial_state)

# Print the path to the goal state
if path:
    print("\nPath to the goal state:")
    for state in path:
        print(state)
else:
    print("No solution found.")
