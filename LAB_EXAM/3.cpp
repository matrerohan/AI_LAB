#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Node class represents a state in the puzzle
class Node
{
public:
    vector<vector<int>> state; // The current state of the puzzle
    Node *parent;              // Pointer to the parent node
    int g;                     // Cost from the initial state to this state
    int h;                     // Heuristic value (estimated cost to reach the goal state)
    int f;                     // Evaluation function value (f = g + h)

    // Constructor to initialize the node
    Node(vector<vector<int>> state, Node *parent, int g, int h)
    {
        this->state = state;
        this->parent = parent;
        this->g = g;
        this->h = h;
        this->f = g + h;
    }

    // Print the state of the puzzle
    void print()
    {
        for (int i = 0; i < state.size(); i++)
        {
            for (int j = 0; j < state[i].size(); j++)
            {
                cout << state[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Generate successors of the current node
    vector<Node *> getSuccessors()
    {
        vector<Node *> successors;
        int x, y;
        for (int i = 0; i < state.size(); i++)
        {
            for (int j = 0; j < state[i].size(); j++)
            {
                if (state[i][j] == 0)
                {
                    x = i;
                    y = j;
                    break;
                }
            }
        }
        if (x > 0)
        {
            vector<vector<int>> newState = state;
            swap(newState[x][y], newState[x - 1][y]);
            successors.push_back(new Node(newState, this, g + 1, 0));
        }
        if (x < 2)
        {
            vector<vector<int>> newState = state;
            swap(newState[x][y], newState[x + 1][y]);
            successors.push_back(new Node(newState, this, g + 1, 0));
        }
        if (y > 0)
        {
            vector<vector<int>> newState = state;
            swap(newState[x][y], newState[x][y - 1]);
            successors.push_back(new Node(newState, this, g + 1, 0));
        }
        if (y < 2)
        {
            vector<vector<int>> newState = state;
            swap(newState[x][y], newState[x][y + 1]);
            successors.push_back(new Node(newState, this, g + 1, 0));
        }
        return successors;
    }
};

// Calculate the heuristic value (number of misplaced tiles)
int calculate_h(vector<vector<int>> state, vector<vector<int>> goal)
{
    int h = 0; // Initialize h to 0
    for (int i = 0; i < state.size(); i++)
    {
        for (int j = 0; j < state[i].size(); j++)
        {
            if (state[i][j] != 0 && state[i][j] != goal[i][j])
            {
                h += 1;
            }
        }
    }
    return h;
}

// Check if a node is in the closed set
int inClosedSet(vector<Node *> closedSet, Node *node)
{
    for (auto n : closedSet)
    {
        if (n->state == node->state)
        {
            return 1;
        }
    }
    return 0;
}

// Comparison function for nodes based on f value
bool compareNodes(Node *a, Node *b)
{
    return a->f > b->f;
}

// A* search algorithm
class AStar
{
public:
    Node *search(Node *start, Node *goal)
    {
        priority_queue<Node *, vector<Node *>, function<bool(Node *, Node *)>> openSet(compareNodes);

        vector<Node *> closedSet;
        openSet.push(start);

        while (!openSet.empty())
        {
            Node *current = openSet.top();
            openSet.pop();

            if (current->state == goal->state)
            {
                printf("Goal found\n");
                return current;
            }

            closedSet.push_back(current);
            vector<Node *> successors = current->getSuccessors();
            for (auto successor : successors)
            {
                if (successor->state == goal->state)
                {
                    return successor;
                }

                if (!inClosedSet(closedSet, successor))
                {
                    successor->h = calculate_h(successor->state, goal->state);
                    successor->f = successor->g + successor->h;
                    openSet.push(successor);
                }
            }
        }
        return nullptr;
    }
};

// Print the solution path
int printSolution(Node *goal)
{
    int moves = 0;
    if (goal == nullptr)
    {
        return moves;
    }
    if (goal->parent != nullptr)
    {
        moves += printSolution(goal->parent);
    }
    goal->print();
    return moves + 1;
}

int main()
{
    int n;
    cout << "Enter the size of the puzzle: ";
    cin >> n;
    vector<vector<int>> startState(n, vector<int>(n));
    vector<vector<int>> goalState(n, vector<int>(n));

    cout << "Enter the initial state of the puzzle:" << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> startState[i][j];
        }
    }

    cout << "Enter the goal state of the puzzle:" << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> goalState[i][j];
        }
    }

    cout << endl;

    cout << "Steps to reach the goal state:" << endl;
    Node *start = new Node(startState, nullptr, 0, 0);
    Node *goal = new Node(goalState, nullptr, 0, 0);

    AStar astar;
    Node *result = astar.search(start, goal);

    int totalMoves = printSolution(result);
    cout << "Total number of moves: " << totalMoves - 1 << endl;
    return 0;
}

/* EX-1 
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

*/