from collections import deque

class JugState:
    def __init__(self, jug_a, jug_b):
        self.jug_a = jug_a
        self.jug_b = jug_b

def print_path(steps):
    for step in steps:
        print(step)

def water_jug_BFS(x, y, z):
    q = deque()
    q.append((JugState(0, 0), []))
    visited = set()
    min_steps = 0

    while q:
        level_size = len(q)
        for _ in range(level_size):
            state, steps = q.popleft()
            jug_a, jug_b = state.jug_a, state.jug_b

            if jug_a == z or jug_b == z or jug_a + jug_b == z:
                steps.append(f"----> Desired goal state reached: Jugs: ({jug_a}, {jug_b}) <----\n")
                print_path(steps)
                return min_steps

            if (jug_a, jug_b) in visited:
                continue

            visited.add((jug_a, jug_b))

            # Fill jug A
            if jug_a < x:
                q.append((JugState(x, jug_b), steps + [f" Fill jug A. Jugs: ({x}, {jug_b})\n"]))

            # Fill jug B
            if jug_b < y:
                q.append((JugState(jug_a, y), steps + [f" Fill jug B. Jugs: ({jug_a}, {y})\n"]))

            # Empty jug A
            if jug_a > 0:
                q.append((JugState(0, jug_b), steps + [f" Empty jug A. Jugs: (0, {jug_b})\n"]))

            # Empty jug B
            if jug_b > 0:
                q.append((JugState(jug_a, 0), steps + [f" Empty jug B. Jugs: ({jug_a}, 0)\n"]))

            # Pour from A to B
            if jug_a + jug_b >= y:
                q.append((JugState(jug_a - (y - jug_b), y), steps + [f" Pour from A to B. Jugs: ({jug_a - (y - jug_b)}, {y})\n"]))
            else:
                q.append((JugState(0, jug_a + jug_b), steps + [f" Pour from A to B. Jugs: (0, {jug_a + jug_b})\n"]))

            # Pour from B to A
            if jug_a + jug_b >= x:
                q.append((JugState(x, jug_b - (x - jug_a)), steps + [f" Pour from B to A. Jugs: ({x}, {jug_b - (x - jug_a)})\n"]))
            else:
                q.append((JugState(jug_a + jug_b, 0), steps + [f" Pour from B to A. Jugs: ({jug_a + jug_b}, 0)\n"]))

        min_steps += 1

    return -1

def main():
    m = int(input("Enter the capacity of jug M: "))
    n = int(input("Enter the capacity of jug N: "))
    d = int(input("Enter the desired amount of water D: "))

    min_steps = water_jug_BFS(m, n, d)
    if min_steps != -1:
        print(f"You can measure {d} liters of water using {m}-liter and {n}-liter jugs.")
        print(f"Minimum number of steps required: {min_steps}")
    else:
        print(f"You cannot measure {d} liters of water using {m}-liter and {n}-liter jugs.")

if __name__ == "__main__":
    main()

'''
/* EX-1
Enter the capacity of jug M: 5
Enter the capacity of jug N: 3
Enter the desired amount of water D: 4
You can measure 4 liters of water using 5-liter and 3-liter jugs.
Minimum number of steps required: 6
Steps:
 Fill jug A. Jugs: (5, 0)
 Pour from A to B. Jugs: (2, 3)
 Empty jug B. Jugs: (2, 0)
 Pour from A to B. Jugs: (0, 2)
 Fill jug A. Jugs: (5, 2)
 Pour from A to B. Jugs: (4, 3)
----> Desired goal state reached: Jugs: (4, 3) <----
*/
'''