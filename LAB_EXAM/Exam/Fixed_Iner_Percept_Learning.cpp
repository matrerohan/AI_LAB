#include <bits/stdc++.h>

using namespace std;

// Define Perceptron class
class Perceptron
{

public:
  // Training Set
  vector<tuple<double, double, int>> data = {
      {0.25, 0.353, 0}, {0.25, 0.471, 1}, {0.5, 0.353, 0}, {0.5, 0.647, 1}, {0.75, 0.705, 0}, {0.75, 0.882, 1}, {1, 0.705, 0}, {1, 1, 1}};

  // Initialize weights with random values
  vector<double> weights = initializeWeights(3);

  // Function to initialize weights with random values between -1 and 1
  vector<double> initializeWeights(int n)
  {
    vector<double> V(n, 0.0);

    srand(time(0));

    generate(V.begin(), V.end(),
             []()
             { return ((double)rand() / RAND_MAX) * 2 - 1; });

    return V;
  }
};

// Function to train the perceptron
pair<vector<double>, vector<int>> train(Perceptron *p)
{
  double learning_rate = 0.1;
  int epochs = 1000;
  bool trained = false;
  vector<int> finalPredicted;

  vector<double> weights =
      p->weights; // Get initial weights from the perceptron object
  vector<tuple<double, double, int>> data =
      p->data; // Get training data from the perceptron object

  // Training loop
  while (trained == false)
  {
    trained = true;
    vector<int> predicted; // Predicted values for each data point

    // Iterate over each data point
    for (auto d : data)
    {
      double x1 = get<0>(d);
      double x2 = get<1>(d);
      int y = get<2>(d);

      double weighted_sum = weights[0] + weights[1] * x1 +
                            weights[2] * x2; // Calculate weighted sum

      int guess =
          weighted_sum > 0.5 ? 1 : 0; // Make prediction based on threshold
      predicted.push_back(guess);
      int error = y - guess; // Calculate error

      // Update weights if prediction is incorrect
      if (guess != y)
      {
        weights[0] += error * learning_rate; // Update bias weight
        weights[1] +=
            error * x1 * learning_rate; // Update weight for first feature
        weights[2] +=
            error * x2 * learning_rate; // Update weight for second feature
        trained = false;                // Set trained to false to continue training
      }
    }

    if (trained == true)
    {
      return make_pair(weights, predicted);
    }

    finalPredicted = predicted; // Store predictions for the last epoch
  }

  return make_pair(weights,
                   finalPredicted); // Return final weights and predictions
}

// Main function
int main()
{
  Perceptron *p = new Perceptron(); // Create a Perceptron object

  // Train the perceptron and get the final weights and predictions
  pair<vector<double>, vector<int>> result = train(p);
  vector<double> final_weights = result.first;
  vector<int> final_predictions = result.second;

  // Print obtained weights
  cout << "Obtained weights: ";
  for (auto w : final_weights)
  {
    cout << w << " ";
  }
  cout << endl;

  // Print target values
  cout << "Target values:    ";
  for (auto d : p->data)
  {
    cout << get<2>(d) << " ";
  }
  cout << endl;

  // Print predicted values
  cout << "Predicted values: ";
  for (auto p : final_predictions)
  {
    cout << p << " ";
  }
  cout << endl;

  delete p; // Free memory allocated for the Perceptron object
  return 0;
}
