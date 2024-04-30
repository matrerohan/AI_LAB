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
            print(' '.join(map(str, row)))
        print()

    def get_successors(self):
        successors = []
        x, y = -1, -1

        for i in range(len(self.state)):
            for j in range(len(self.state[i])):
                if self.state[i][j] == 0:
                    x, y = i, j
                    break

        moves = [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]
        for new_x, new_y in moves:
            if 0 <= new_x < len(self.state) and 0 <= new_y < len(self.state[0]):
                new_state = [row[:] for row in self.state]
                new_state[x][y], new_state[new_x][new_y] = new_state[new_x][new_y], new_state[x][y]
                successors.append(Node(new_state, self, self.g + 1, 0))
        return successors

def calculate_h(state, goal):
    h = 0
    for i in range(len(state)):
        for j in range(len(state[i])):
            if state[i][j] != 0 and state[i][j] != goal[i][j]:
                h += 1
    return h

def in_closed_set(closed_set, node):
    for n in closed_set:
        if n.state == node.state:
            return True
    return False

class AStar:
    def __init__(self):
        pass

    def search(self, start, goal):
        open_set = []
        closed_set = []

        heapq.heappush(open_set, start)

        while open_set:
            current = heapq.heappop(open_set)

            if current.state == goal.state:
                print("Goal found")
                return current

            closed_set.append(current)
            successors = current.get_successors()
            for successor in successors:
                if successor.state == goal.state:
                    return successor

                if not in_closed_set(closed_set, successor):
                    successor.h = calculate_h(successor.state, goal.state)
                    successor.f = successor.g + successor.h
                    heapq.heappush(open_set, successor)

        return None

def print_solution(goal):
    moves = 0
    if goal is None:
        return moves
    if goal.parent is not None:
        moves += print_solution(goal.parent)
    goal.print_state()
    print()
    return moves + 1

if __name__ == "__main__":
    start_state = []
    goal_state = []

    print("Enter the initial state:")
    for _ in range(3):
        row = list(map(int, input().split()))
        start_state.append(row)

    print("Enter the goal state:")
    for _ in range(3):
        row = list(map(int, input().split()))
        goal_state.append(row)

    print("Steps:\n")

    start = Node(start_state, None, 0, 0)
    goal = Node(goal_state, None, 0, 0)

    astar = AStar()
    result = astar.search(start, goal)

    total_moves = print_solution(result)
    print("\nTotal number of moves:", total_moves - 1)
