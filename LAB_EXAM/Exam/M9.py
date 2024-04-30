from itertools import permutations

def solve_cryptarithm():
    # Mapping letters to digits
    letters = 'SENDMORY'
    # Ensure the first letter of each word cannot be 0
    for perm in permutations(range(10), len(letters)):
        if perm[letters.index('S')] == 0 or perm[letters.index('M')] == 0:
            continue  # Skip permutations where S or M is assigned to 0
        mapping = dict(zip(letters, perm))

        # Constructing integers from letters
        S, E, N, D, M, O, R, Y = [mapping[char] for char in letters]

        send = S*1000 + E*100 + N*10 + D
        more = M*1000 + O*100 + R*10 + E
        money = M*10000 + O*1000 + N*100 + E*10 + Y

        # Checking if the equation holds
        if send + more == money:
            print(f"Solution found: SEND = {send}, MORE = {more}, MONEY = {money}")
            return

    print("No solution found")

# Main function to execute the solution
if __name__ == "__main__":
    solve_cryptarithm()
