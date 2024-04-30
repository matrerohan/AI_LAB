import time
from collections import defaultdict
from typing import List, Tuple

class Graph:
    def __init__(self, V: int):
        self.V = V
        self.adj = defaultdict(list)  # Adjacency list representation

    def add_edge(self, u: int, v: int, weight: int):
        self.adj[u].append((v, weight))

    def print_all_paths(self, s: int, d: int) -> List[Tuple[List[int], int]]:
        def dfs_traversal(u: int, visited: List[bool], path: List[int], path_index: int, total_weight: int, all_paths: List[Tuple[List[int], int]]):
            visited[u] = True
            path.append(u)

            nonlocal min_path_weight

            if u == d and len(path) == self.V:
                all_paths.append((path.copy(), total_weight))
                min_path_weight = min(min_path_weight, total_weight)
            else:
                for neighbor, weight in self.adj[u]:
                    if not visited[neighbor]:
                        dfs_traversal(neighbor, visited, path, path_index + 1, total_weight + weight, all_paths)

            path.pop()
            visited[u] = False

        visited = [False] * self.V
        path = []
        all_paths = []
        min_path_weight = float('inf')

        dfs_traversal(s, visited, path, 0, 0, all_paths)

        return [(path, weight) for path, weight in all_paths if weight == min_path_weight]

if __name__ == "__main__":
    g = Graph(8)

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

    s, d = 0, 3

    start = time.time()  # Start timer

    all_paths = g.print_all_paths(s, d)

    if all_paths:
        min_path, min_weight = all_paths[0]
        print("Path with the minimum cost:")
        print("Path:", min_path)
        print("Total Weight:", min_weight)
    else:
        print(f"No path found from {s} to {d}")

    end = time.time()  # Stop timer
    print("Execution time:", end - start, "seconds")
