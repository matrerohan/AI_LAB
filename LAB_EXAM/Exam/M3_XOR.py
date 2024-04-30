import random
import numpy as np

class MultiLayerPerceptron:
    def __init__(self):
        # Data points with their corresponding labels (for XOR problem)
        self.data = [
            (0, 0, 0),
            (0, 1, 1),
            (1, 0, 1),
            (1, 1, 0)
        ]
        # Number of input, hidden, and output neurons
        self.input_neurons = 2
        self.hidden_neurons = 2
        self.output_neurons = 1
        # Weight matrices with initialized weights
        self.weights_input_hidden = self.initialize_weights(self.input_neurons, self.hidden_neurons)
        self.weights_hidden_output = self.initialize_weights(self.hidden_neurons, self.output_neurons)

    # Function to initialize weights randomly
    def initialize_weights(self, n, m):
        # Weight matrix of size (n x m) initialized with random values between -1 and 1
        return np.random.uniform(-1, 1, size=(n, m))

    # Sigmoid activation function
    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    # Derivative of sigmoid function
    def sigmoid_derivative(self, x):
        return x * (1 - x)

    # Forward propagation
    def forward_propagation(self, inputs):
        # Calculate hidden layer activations
        hidden_inputs = np.dot(inputs, self.weights_input_hidden)
        hidden_outputs = self.sigmoid(hidden_inputs)

        # Calculate output layer activations
        final_inputs = np.dot(hidden_outputs, self.weights_hidden_output)
        final_outputs = self.sigmoid(final_inputs)

        return hidden_outputs, final_outputs

    # Backpropagation
    def backpropagation(self, inputs, hidden_outputs, final_outputs, target):
        # Calculate output layer error
        output_errors = target - final_outputs
        # Calculate output layer gradients
        output_gradients = output_errors * self.sigmoid_derivative(final_outputs)
        # Update weights between hidden and output layer
        self.weights_hidden_output += np.dot(hidden_outputs.T, output_gradients)

        # Calculate hidden layer error
        hidden_errors = np.dot(output_errors, self.weights_hidden_output.T)
        # Calculate hidden layer gradients
        hidden_gradients = hidden_errors * self.sigmoid_derivative(hidden_outputs)
        # Update weights between input and hidden layer
        self.weights_input_hidden += np.dot(inputs.T, hidden_gradients)

    # Training function
    def train(self):
        learning_rate = 0.1  # Learning rate
        epochs = 10000       # Maximum number of training epochs

        for epoch in range(epochs):
            for input_data in self.data:
                inputs = np.array(input_data[:2]).reshape(1, self.input_neurons)
                target = np.array(input_data[2]).reshape(1, self.output_neurons)

                # Forward propagation
                hidden_outputs, final_outputs = self.forward_propagation(inputs)

                # Backpropagation
                self.backpropagation(inputs, hidden_outputs, final_outputs, target)

        print("Training completed.")

    # Prediction function
    def predict(self, inputs):
        _, final_outputs = self.forward_propagation(inputs)
        return final_outputs.round()

# Main function
def main():
    mlp = MultiLayerPerceptron()  # Create MLP object
    mlp.train()                   # Train MLP

    # Test predictions
    test_data = [(0, 0), (0, 1), (1, 0), (1, 1)]
    for data in test_data:
        inputs = np.array(data).reshape(1, mlp.input_neurons)
        prediction = mlp.predict(inputs)
        print(f"Input: {data}, Prediction: {prediction[0][0]}")

if __name__ == "__main__":
    main()
