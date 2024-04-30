from collections import deque
from typing import List, Tuple

class Graph:
    def __init__(self, V: int):
        self.adj = [[] for _ in range(V)]  # Adjacency list representation

    def add_edge(self, u: int, v: int, weight: int):
        self.adj[u].append((v, weight))

    def find_paths(self, src: int, dst: int) -> List[Tuple[List[int], int]]:
        paths = []
        q = deque([(src, [src], 0)])  # Queue of (node, path, total weight)

        while q:
            current, current_path, total_weight = q.popleft()
            if current == dst and len(current_path) == len(self.adj):
                paths.append((current_path, total_weight))

            for neighbor, weight in self.adj[current]:
                if neighbor not in current_path:
                    q.append((neighbor, current_path + [neighbor], total_weight + weight))

        return paths

if __name__ == "__main__":
    V = 8
    g = Graph(V)

    g.add_edge(0, 1, 2)
    g.add_edge(0, 6, 6)
    g.add_edge(1, 0, 2)
    g.add_edge(1, 2, 7)
    g.add_edge(1, 4, 2)
    g.add_edge(2, 1, 7)
    g.add_edge(2, 3, 3)
    g.add_edge(2, 5, 3)
    g.add_edge(3, 2, 3)
    g.add_edge(3, 7, 2)
    g.add_edge(4, 1, 2)
    g.add_edge(4, 5, 2)
    g.add_edge(4, 6, 1)
    g.add_edge(5, 2, 3)
    g.add_edge(5, 4, 2)
    g.add_edge(5, 7, 2)
    g.add_edge(6, 0, 6)
    g.add_edge(6, 4, 1)
    g.add_edge(6, 7, 4)
    g.add_edge(7, 3, 2)
    g.add_edge(7, 5, 2)
    g.add_edge(7, 6, 4)

    src = 0
    dst = 3

    print(f"Paths from src {src} to dst {dst} are:")
    paths = g.find_paths(src, dst)

    min_path = min(paths, key=lambda x: x[1])

    print("Shortest path:", min_path[0])
    print("Total Weight:", min_path[1])
