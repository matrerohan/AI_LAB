import heapq

def a_star(graph, start, goal, heuristic):
    # Priority queue to store nodes based on total cost (f = g + h)
    open_set = []
    heapq.heappush(open_set, (0, start))
    
    # Dictionaries to store actual cost (g) and the path
    g_cost = {start: 0}
    came_from = {start: None}

    while open_set:
        # Get the node with the lowest f score
        _, current = heapq.heappop(open_set)

        # If we've reached the goal node, reconstruct and return the path
        if current == goal:
            path = []
            while current:
                path.append(current)
                current = came_from[current]
            return path[::-1]  # Return reversed path

        # Explore neighbors
        for neighbor, cost in graph[current]:
            new_g_cost = g_cost[current] + cost

            if neighbor not in g_cost or new_g_cost < g_cost[neighbor]:
                g_cost[neighbor] = new_g_cost
                f_cost = new_g_cost + heuristic(neighbor, goal)
                heapq.heappush(open_set, (f_cost, neighbor))
                came_from[neighbor] = current

    return None

# Graph representation
graph = {
    'A': [('B', 2), ('E', 7)],
    'B': [('A', 2), ('C', 9)],
    'C': [('B', 9), ('D', 1), ('G', 99)],
    'D': [('C', 1), ('E', 1)],
    'E': [('A', 7), ('D', 1), ('G', 6)],
    'G': [('C', 99), ('E', 6)],
}

# Heuristic function for A* (Manhattan distance for simplicity)
def heuristic(node, goal):
    # Example heuristic function to estimate cost to goal
    # For simplicity, using direct distance (0 for now) or other estimations if available
    heuristic_estimates = {
        ('A', 'G'): 10, ('B', 'G'): 20, ('C', 'G'): 1, # etc...
    }
    return heuristic_estimates.get((node, goal), 0)

# Example usage:
start_node = 'A'
goal_node = 'G'
path = a_star(graph, start_node, goal_node, heuristic)
print("Shortest Path: ", path)