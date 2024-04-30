import heapq

class Node:
    def __init__(self, state, parent, g, h):
        self.state = state
        self.parent = parent
        self.g = g
        self.h = h
        self.f = g + h

    def __lt__(self, other):
        return self.f < other.f

    def print_state(self):
        for row in self.state:
            print(*row)
        print()

    def get_successors(self):
        successors = []
        x, y = next((i, j) for i, row in enumerate(self.state) for j, val in enumerate(row) if val == 0)
        moves = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        for dx, dy in moves:
            new_x, new_y = x + dx, y + dy
            if 0 <= new_x < len(self.state) and 0 <= new_y < len(self.state[0]):
                new_state = [row[:] for row in self.state]
                new_state[x][y], new_state[new_x][new_y] = new_state[new_x][new_y], new_state[x][y]
                successors.append(Node(new_state, self, self.g + 1, 0))
        return successors

def calculate_h(state, goal):
    return sum(1 for i in range(len(state)) for j in range(len(state[0])) if state[i][j] != 0 and state[i][j] != goal[i][j])

def in_closed_set(closed_set, node):
    return any(n.state == node.state for n in closed_set)

class AStar:
    def __init__(self):
        self.open_set = []
        heapq.heapify(self.open_set)
        self.closed_set = set()

    def search(self, start, goal):
        heapq.heappush(self.open_set, start)
        while self.open_set:
            current = heapq.heappop(self.open_set)
            if current.state == goal.state:
                return current
            self.closed_set.add(tuple(map(tuple, current.state)))
            successors = current.get_successors()
            for successor in successors:
                if successor.state == goal.state:
                    return successor
                if tuple(map(tuple, successor.state)) not in self.closed_set:
                    successor.h = calculate_h(successor.state, goal.state)
                    successor.f = successor.g + successor.h
                    heapq.heappush(self.open_set, successor)
        return None

def print_solution(goal):
    moves = 0
    if goal is None:
        return moves
    if goal.parent is not None:
        moves += print_solution(goal.parent)
    goal.print_state()
    return moves + 1

def main():
    n = int(input("Enter the size of the puzzle: "))
    print("Enter the initial state of the puzzle:")
    start_state = [list(map(int, input().split())) for _ in range(n)]
    print("Enter the goal state of the puzzle:")
    goal_state = [list(map(int, input().split())) for _ in range(n)]

    print()

    print("Steps to reach the goal state:")
    start = Node(start_state, None, 0, 0)
    goal = Node(goal_state, None, 0, 0)

    astar = AStar()
    result = astar.search(start, goal)

    total_moves = print_solution(result)
    print("Total number of moves:", total_moves - 1)

if __name__ == "__main__":
    main()

'''
EX-1 
(i) Normal Case:
Enter the size of the puzzle: 3
Enter the initial state of the puzzle:
1 2 3
8 0 4
7 6 5
Enter the goal state of the puzzle:
2 8 1
0 4 3
7 6 5

(ii) Best Case:  Initial State = Goal State
Enter the size of the puzzle: 3
Enter the initial state of the puzzle:
1 2 3
8 0 4
7 6 5
Enter the goal state of the puzzle:
1 2 3
8 0 4
7 6 5

(iii) Average Case: 
Enter the size of the puzzle: 3
Enter the initial state of the puzzle:
8 3 5 
4 1 6
2 7 0
Enter the goal state of the puzzle:
1 2 3
8 0 4
7 6 5

(iv) Worst Case: Goal State is transpose (Reverse) of initial State.
Enter the size of the puzzle: 3
Enter the initial state of the puzzle:
1 2 3
8 0 4
7 6 5
Enter the goal state of the puzzle:
5 4 3
6 0 8
7 2 1
'''