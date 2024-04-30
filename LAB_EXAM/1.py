from queue import PriorityQueue
from collections import defaultdict
import time

INF = float('inf')

def print_path(parent, current):
    path = []
    while current != -1:
        path.append(current)
        current = parent[current]
    print("Minimum Path:", end=" ")
    print(*reversed(path))

def bfs(adj, V, src, dest):
    start_time = time.time()

    pq = PriorityQueue()
    dist = [INF] * V
    parent = [-1] * V

    pq.put((0, src))
    dist[src] = 0

    while not pq.empty():
        u = pq.get()[1]

        if u == dest:
            break

        for v, weight in adj[u]:
            if dist[v] > dist[u] + weight:
                dist[v] = dist[u] + weight
                parent[v] = u
                pq.put((dist[v], v))

    stop_time = time.time()
    duration = (stop_time - start_time) * 1e6

    if dist[dest] == INF:
        print("\nNo path found from", src, "to", dest)
    else:
        print("\nCost of Shortest bfs path from", src, "to", dest, "is:", dist[dest])
        print_path(parent, dest)
        print("BFS Execution Time: {:.2f} microseconds".format(duration))

def dfs(adj, V, src, dest):
    start_time = time.time()

    stack = [(src, 0)]
    visited = [False] * V
    parent = [-1] * V
    cost = [INF] * V

    cost[src] = 0

    while stack:
        u, current_cost = stack.pop()

        if not visited[u]:
            visited[u] = True

            if u == dest:
                break

            for v, weight in adj[u]:
                if not visited[v]:
                    new_cost = current_cost + weight
                    if new_cost < cost[v]:
                        cost[v] = new_cost
                        parent[v] = u
                        stack.append((v, new_cost))

    stop_time = time.time()
    duration = (stop_time - start_time) * 1e6

    if not visited[dest]:
        print("\nNo path found from", src, "to", dest)
    else:
        print("\nCost of Shortest dfs path from", src, "to", dest, "is:", cost[dest])
        print_path(parent, dest)
        print("DFS Execution Time: {:.2f} microseconds".format(duration))

def main():
    V = int(input("Enter the number of vertices (V): "))
    adj = defaultdict(list)

    E = int(input("Enter the number of edges (E): "))

    print("Enter current node, next node, and weight for each edge:")
    for _ in range(E):
        u, v, w = map(int, input().split())
        adj[u].append((v, w))
        adj[v].append((u, w))

    source = int(input("Enter the source node: "))
    destination = int(input("Enter the destination node: "))

    bfs(adj, V, source, destination)
    dfs(adj, V, source, destination)

if __name__ == "__main__":
    main()

'''
// Input: Ex-1

// V = 8 , E = 11
/*
0 1 2
0 6 6
1 2 7
1 4 2
2 3 3
2 5 3
3 7 2
4 5 2
4 6 1
5 7 2
6 7 4
*/

// Source Node: 0 , Dest. Node: 3


// Input: Ex-2

// V = 9 , E = 15
/*
1 2 10
1 3 7
2 4 15
2 5 10
2 6 12
3 5 15
3 6 7
4 7 9
4 8 13
5 7 12
5 8 8
6 7 22
6 8 15
7 9 9
8 9 5
*/

// Source Node: 0 , Dest. Node: 9
'''