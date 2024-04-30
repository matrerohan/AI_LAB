import random

class Perceptron:
    def __init__(self):
        # Data points with their corresponding labels (for OR problem)
        self.data = [
            (0, 0, 0),
            (0, 1, 1),
            (1, 0, 1),
            (1, 1, 1)
        ]
        # Weight vector with initialized weights
        self.weights = self.initialize_weights(3)

    # Function to initialize weights randomly
    def initialize_weights(self, n):
        # Vector of size n initialized with random values between -1 and 1
        return [random.uniform(-1, 1) for _ in range(n)]

# Function to train the perceptron
def train(p):
    learning_rate = 0.1  # Learning rate
    epochs = 1000        # Maximum number of training epochs
    trained = False      # Training termination condition
    final_predicted = [] # Final predicted outputs

    weights = p.weights  # Initial weights
    data = p.data        # Training data

    # Training loop
    while not trained:
        trained = True        # Assume convergence
        predicted = []        # Predicted outputs for each data point
        for x1, x2, y in data:  # For each data point
            # Calculate weighted sum
            weighted_sum = weights[0] + weights[1] * x1 + weights[2] * x2
            # Predict output
            guess = 1 if weighted_sum >= 0 else 0
            predicted.append(guess)  # Store predicted output
            # Calculate error
            error = y - guess
            # Update weights if prediction is incorrect
            if guess != y:
                weights[0] += error * learning_rate
                weights[1] += error * x1 * learning_rate
                weights[2] += error * x2 * learning_rate
                trained = False  # Model not yet trained to convergence
        if trained:  # If model is trained to convergence
            return weights, predicted  # Return final weights and predictions
        final_predicted = predicted  # Store predicted outputs for the last epoch
    return weights, final_predicted  # Return final weights and predictions

# Main function
def main():
    p = Perceptron()          # Create perceptron object
    final_weights, final_predictions = train(p)  # Train perceptron

    # Print final weights
    print("Final Weights:", *final_weights)

    # Print final predictions
    print("Final Predictions:", *final_predictions)

if __name__ == "__main__":
    main()
