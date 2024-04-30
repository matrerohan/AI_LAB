import random

# Define the objective function (example: maximize f(x) = -x^2)
def objective_function(x):
    return -x**2

# Define the Hill Climbing algorithm
def hill_climbing(max_iter=1000, step_size=0.1):
    # Initialize the current state randomly
    current_state = random.uniform(-10, 10)
    
    for _ in range(max_iter):
        # Generate a new candidate state by adding a small random value to the current state
        candidate_state = current_state + random.uniform(-step_size, step_size)
        
        # Calculate the objective function values for the current state and the candidate state
        current_value = objective_function(current_state)
        candidate_value = objective_function(candidate_state)
        
        # Update the current state if the candidate state has a higher objective function value
        if candidate_value > current_value:
            current_state = candidate_state
    
    return current_state, objective_function(current_state)

# Run the Hill Climbing algorithm
best_solution, best_value = hill_climbing()
print("Best Solution:", best_solution)
print("Best Value:", best_value)