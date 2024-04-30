#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <set>

using namespace std;

struct JugState
{
    int jug_a;
    int jug_b;
};

int water_jug_BFS(int x, int y, int z, vector<string> &steps)
{
    queue<pair<JugState, string>> q;
    q.push({{0, 0}, ""});
    set<pair<int, int>> visited;
    int min_steps = 0;

    while (!q.empty())
    {
        int level_size = q.size(); // Get the current level size
        for (int i = 0; i < level_size; ++i)
        {
            auto state = q.front();
            q.pop();
            int jug_a = state.first.jug_a;
            int jug_b = state.first.jug_b;
            string current_step = state.second;

            if (jug_a == z || jug_b == z || jug_a + jug_b == z)
            {
                steps.push_back(current_step + "----> Desired goal state reached: Jugs: (" + to_string(jug_a) + ", " + to_string(jug_b) + ") <----\n");
                return min_steps;
            }

            if (visited.find({jug_a, jug_b}) != visited.end())
            {
                continue;
            }

            visited.insert({jug_a, jug_b});

            // Fill jug A
            if (jug_a < x)
            {
                q.push({{x, jug_b}, current_step + " Fill jug A. Jugs: (" + to_string(x) + ", " + to_string(jug_b) + ")\n"});
            }

            // Fill jug B
            if (jug_b < y)
            {
                q.push({{jug_a, y}, current_step + " Fill jug B. Jugs: (" + to_string(jug_a) + ", " + to_string(y) + ")\n"});
            }

            // Empty jug A
            if (jug_a > 0)
            {
                q.push({{0, jug_b}, current_step + " Empty jug A. Jugs: (0, " + to_string(jug_b) + ")\n"});
            }

            // Empty jug B
            if (jug_b > 0)
            {
                q.push({{jug_a, 0}, current_step + " Empty jug B. Jugs: (" + to_string(jug_a) + ", 0)\n"});
            }

            // Pour from A to B
            if (jug_a + jug_b >= y)
            {
                q.push({{jug_a - (y - jug_b), y}, current_step + " Pour from A to B. Jugs: (" + to_string(jug_a - (y - jug_b)) + ", " + to_string(y) + ")\n"});
            }
            else
            {
                q.push({{0, jug_a + jug_b}, current_step + " Pour from A to B. Jugs: (0, " + to_string(jug_a + jug_b) + ")\n"});
            }

            // Pour from B to A
            if (jug_a + jug_b >= x)
            {
                q.push({{x, jug_b - (x - jug_a)}, current_step + " Pour from B to A. Jugs: (" + to_string(x) + ", " + to_string(jug_b - (x - jug_a)) + ")\n"});
            }
            else
            {
                q.push({{jug_a + jug_b, 0}, current_step + " Pour from B to A. Jugs: (" + to_string(jug_a + jug_b) + ", 0)\n"});
            }
        }
        min_steps++; // Increment steps after processing each level
    }

    return -1; // No solution found
}

int main()
{
    int m, n, d;

    // Take input from user
    cout << "Enter the capacity of jug M: ";
    cin >> m;
    cout << "Enter the capacity of jug N: ";
    cin >> n;
    cout << "Enter the desired amount of water D: ";
    cin >> d;

    vector<string> steps;
    int min_steps = water_jug_BFS(m, n, d, steps);
    if (min_steps != -1)
    {
        cout << "You can measure " << d << " liters of water using " << m << "-liter and " << n << "-liter jugs." << endl;
        cout << "Minimum number of steps required: " << min_steps << endl;
        cout << "Steps:" << endl;
        for (const auto &step : steps)
        {
            cout << step;
        }
    }
    else
    {
        cout << "You cannot measure " << d << " liters of water using " << m << "-liter and " << n << "-liter jugs." << endl;
    }

    return 0;
}

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