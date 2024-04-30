import heapq

class Graph:
    def _init_(self):
        self.adj_list = {}

    def add_edge(self, u, v, weight):
        if u not in self.adj_list:
            self.adj_list[u] = []
        self.adj_list[u].append((v, weight))

    def get_neighbors(self, node):
        return self.adj_list.get(node, [])

def astar(graph, start, goal, heuristic):
    open_list = []
    closed_set = set()
    heapq.heappush(open_list, (0, start))
    
    while open_list:
        f, current = heapq.heappop(open_list)
        
        if current == goal:
            return current
        
        closed_set.add(current)
        
        for neighbor, cost in graph.get_neighbors(current):
            if neighbor in closed_set:
                continue
            
            g = f - heuristic[current]  # subtracting heuristic value of current node
            h = heuristic[neighbor]
            f = g + cost + h  # adding heuristic value of neighbor
            heapq.heappush(open_list, (f, neighbor))
    
    return None

# Example usage:
graph = Graph()
graph.add_edge('A', 'B', 1)
graph.add_edge('A', 'C', 2)
graph.add_edge('B', 'D', 3)
graph.add_edge('C', 'D', 1)
graph.add_edge('D', 'E', 2)

heuristic_values = {'A': 5, 'B': 4, 'C': 3, 'D': 2, 'E': 1}

start_node = 'A'
goal_node = 'E'

path = astar(graph, start_node, goal_node, heuristic_values)
if path:
    print("Path found:", path)
else:
    print("No path found.")