#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>
#define INF 0x3f3f3f3f
using namespace std;
using namespace std::chrono;

void printPath(const vector<int> &parent, int current)
{
    stack<int> path;

    while (current != -1)
    {
        path.push(current);
        current = parent[current];
    }

    cout << "Minimum Path: ";
    while (!path.empty())
    {
        cout << path.top() << " ";
        path.pop();
    }
    cout << endl;
}

void bfs(vector<vector<pair<int, int>>> &adj, int V, int src, int dest)
{
    auto start_time = high_resolution_clock::now();

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(V, INF);
    vector<int> parent(V, -1);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (u == dest)
            break;

        for (const auto &edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;
            
            // Relaxation
            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop_time - start_time);
    if (dist[dest] == INF)
    {
        cout << endl;
        cout << "No path found from " << src << " to " << dest << endl;
    }
    else
    {
        cout << endl;
        cout << "Cost of Shortest bfs path from " << src << " to " << dest << " is: " << dist[dest] << endl;
        printPath(parent, dest);
        cout << "BFS Execution Time: " << duration.count() << " microseconds" << endl;
    }
}

void dfs(vector<vector<pair<int, int>>> &adj, int V, int src, int dest)
{
    auto start_time = high_resolution_clock::now();

    stack<pair<int, int>> st;
    vector<int> visited(V, false);
    vector<int> parent(V, -1);
    vector<int> cost(V, INF);

    st.push({src, 0});
    cost[src] = 0;

    while (!st.empty())
    {
        int u = st.top().first;
        int current_cost = st.top().second;
        st.pop();

        if (!visited[u])
        {
            visited[u] = true;

            if (u == dest)
                break;

            for (const auto &edge : adj[u])
            {
                int v = edge.first;
                int weight = edge.second;

                if (!visited[v])
                {
                    int new_cost = current_cost + weight;
                    if (new_cost < cost[v])
                    {
                        cost[v] = new_cost;
                        parent[v] = u;
                        st.push({v, new_cost});
                    }
                }
            }
        }
    }

    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop_time - start_time);

    if (!visited[dest])
    {
        cout << endl;
        cout << "No path found from " << src << " to " << dest << endl;
    }
    else
    {
        cout << endl;
        cout << "Cost of Shortest dfs path from " << src << " to " << dest << " is: " << cost[dest] << endl;
        printPath(parent, dest);
        cout << "DFS Execution Time: " << duration.count() << " microseconds" << endl;
    }
}

int main()
{
    int V;
    cout << "Enter the number of vertices (V): ";
    cin >> V;

    // Create an adjacency list
    vector<vector<pair<int, int>>> adj(V);

    int E;
    cout << "Enter the number of edges (E): ";
    cin >> E;

    cout << "Enter current node, next node, and weight for each edge:" << endl;
    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int source, destination;
    cout << "Enter the source node: ";
    cin >> source;

    cout << "Enter the destination node: ";
    cin >> destination;

    bfs(adj, V, source, destination);
    dfs(adj, V, source, destination);

    return 0;
}

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
