#include <iostream>
#include <vector>
using namespace std;

class Perceptron
{

public:
    // Data points with their corresponding labels
    vector<tuple<double, double, int>> data = {
        {0.25, 0.353, 0}, {0.25, 0.471, 1}, {0.5, 0.353, 0}, {0.5, 0.647, 1}, {0.75, 0.705, 0}, {0.75, 0.882, 1}, {1, 0.705, 0}, {1, 1, 1}};

    // Weight vector with initialized weights
    vector<double> weights = initializeWeights(3);

    // Function to initialize weights randomly
    vector<double> initializeWeights(int n)
    {
        vector<double> V(n, 0.0); // Vector of size n initialized with zeros
        srand(time(0));           // Seed for random number generation
        // Generate random weights between -1 and 1
        generate(V.begin(), V.end(), []()
                 { return ((double)rand() / RAND_MAX) * 2 - 1; });
        return V;
    }
};

// Function to train the perceptron
pair<vector<double>, vector<int>> train(Perceptron *p)
{
    double learning_rate = 0.1; // Learning rate
    int epochs = 1000;          // Maximum number of training epochs
    bool trained = false;       // Training termination condition
    vector<int> finalPredicted; // Final predicted outputs

    vector<double> weights = p->weights;               // Initial weights
    vector<tuple<double, double, int>> data = p->data; // Training data

    // Training loop
    while (trained == false)
    {
        trained = true;        // Assume convergence
        vector<int> predicted; // Predicted outputs for each data point
        for (auto d : data)    // For each data point
        {
            double x1 = get<0>(d); // Feature 1
            double x2 = get<1>(d); // Feature 2
            int y = get<2>(d);     // Actual label

            // Calculate weighted sum
            double weighted_sum = weights[0] + weights[1] * x1 + weights[2] * x2;

            // Predict output
            int guess = weighted_sum > 0.5 ? 1 : 0;
            predicted.push_back(guess); // Store predicted output

            // Calculate error
            int error = y - guess;

            // Update weights if prediction is incorrect
            if (guess != y)
            {
                weights[0] += error * learning_rate;
                weights[1] += error * x1 * learning_rate;
                weights[2] += error * x2 * learning_rate;
                trained = false; // Model not yet trained to convergence
            }
        }
        if (trained == true) // If model is trained to convergence
        {
            return make_pair(weights, predicted); // Return final weights and predictions
        }
        finalPredicted = predicted; // Store predicted outputs for the last epoch
    }
    return make_pair(weights, finalPredicted); // Return final weights and predictions
}

// Main function
int main()
{
    Perceptron *p = new Perceptron();                    // Create perceptron object
    pair<vector<double>, vector<int>> result = train(p); // Train perceptron
    vector<double> final_weights = result.first;         // Get final weights
    vector<int> final_predictions = result.second;       // Get final predictions

    // Print final weights
    for (auto w : final_weights)
    {
        cout << w << " ";
    }
    cout << endl;

    // Print final predictions
    for (auto p : final_predictions)
    {
        cout << p << " ";
    }
    cout << endl;
    return 0; // Exit program
}
