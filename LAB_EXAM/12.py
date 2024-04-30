import math

orig_board = ["0", "1", "2", "3", "4", "5", "6", "7", "8"]

# human
hu_player = "X"

# ai
ai_player = "O"

# returns list of the indexes of empty spots on the board
def empty_indices(board):
    return [i for i in range(len(board)) if board[i] != "O" and board[i] != "X"]

# winning combinations using the board indices
def winning(board, player):
    return ((board[0] == player and board[1] == player and board[2] == player) or
            (board[3] == player and board[4] == player and board[5] == player) or
            (board[6] == player and board[7] == player and board[8] == player) or
            (board[0] == player and board[3] == player and board[6] == player) or
            (board[1] == player and board[4] == player and board[7] == player) or
            (board[2] == player and board[5] == player and board[8] == player) or
            (board[0] == player and board[4] == player and board[8] == player) or
            (board[2] == player and board[4] == player and board[6] == player))

# the main minimax function
class Move:
    def __init__(self, index, score):
        self.index = index
        self.score = score

def minimax(new_board, player):
    # available spots
    avail_spots = empty_indices(new_board)

    # checks for the terminal states such as win, lose, and tie
    # and returning a value accordingly
    if winning(new_board, hu_player):
        return Move(-1, -10)
    elif winning(new_board, ai_player):
        return Move(-1, 10)
    elif len(avail_spots) == 0:
        return Move(-1, 0)

    # an array to collect all the objects
    moves = []

    # loop through available spots
    for i in avail_spots:
        # create an object for each and store the index of that spot
        move = Move(i, None)

        # set the empty spot to the current player
        new_board[i] = player

        # collect the score resulted from calling minimax
        # on the opponent of the current player
        if player == ai_player:
            result = minimax(new_board, hu_player)
            move.score = result.score
        else:
            result = minimax(new_board, ai_player)
            move.score = result.score

        # reset the spot to empty
        new_board[i] = str(i)

        # push the object to the array
        moves.append(move)

    # if it is the computer's turn loop over the moves and choose the move with
    # the highest score
    best_move = 0
    if player == ai_player:
        best_score = -math.inf
        for i in range(len(moves)):
            if moves[i].score > best_score:
                best_score = moves[i].score
                best_move = i
    else:
        # else loop over the moves and choose the move with the lowest score
        best_score = math.inf
        for i in range(len(moves)):
            if moves[i].score < best_score:
                best_score = moves[i].score
                best_move = i

    # return the chosen move (object) from the moves array
    return moves[best_move]

# Print the Tic Tac Toe board
def print_board(board):
    for i in range(3):
        for j in range(3):
            print(board[i * 3 + j], end=" ")
        print()
    print()

def main():
    board = orig_board[:]
    moves = 0

    while True:
        # Human player's turn
        if moves % 2 == 0:
            move_index = int(input("Human player's turn (X).\nEnter the index (0-8) to place your move: "))
            if move_index < 0 or move_index > 8 or board[move_index] != str(move_index):
                print("Invalid move! Try again.")
                continue
            board[move_index] = hu_player
        # AI player's turn
        else:
            print("AI player's turn (O).")
            best_move = minimax(board, ai_player)
            board[best_move.index] = ai_player

        # Print the current board
        print_board(board)

        # Check for a win or draw
        if winning(board, hu_player):
            print("Human player (X) wins!")
            break
        elif winning(board, ai_player):
            print("AI player (O) wins!")
            break
        elif len(empty_indices(board)) == 0:
            print("It's a draw!")
            break

        # Increment moves counter
        moves += 1

if __name__ == "__main__":
    main()

'''
/*
Human player's turn (X).
Enter the index (0-8) to place your move: 1
0 X 2 
3 4 5 
6 7 8 

AI player's turn (O).
O X 2 
3 4 5 
6 7 8 

Human player's turn (X).
Enter the index (0-8) to place your move: 4
O X 2 
3 X 5 
6 7 8 

AI player's turn (O).
O X 2 
3 X 5 
6 O 8 

Human player's turn (X).
Enter the index (0-8) to place your move: 5
O X 2 
3 X X 
6 O 8 

AI player's turn (O).
O X 2 
O X X 
6 O 8 

Human player's turn (X).
Enter the index (0-8) to place your move: 6
O X 2 
O X X 
X O 8 

AI player's turn (O).
O X O 
O X X 
X O 8 

Human player's turn (X).
Enter the index (0-8) to place your move: 8
O X O 
O X X 
X O X 

It's a draw!
*/
'''