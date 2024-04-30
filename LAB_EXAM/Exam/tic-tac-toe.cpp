#include <iostream>
#include <vector>
#include <limits>
using namespace std;

vector<string> origBoard = { "0", "1", "2", "3", "4", "5", "6", "7", "8" };

// human
string huPlayer = "X";

// ai
string aiPlayer = "O";

// returns vector of the indexes of empty spots on the board
vector<int> emptyIndexies(const vector<string>& board) {
    vector<int> indexes;
    for (int i = 0; i < board.size(); ++i) {
        if (board[i] != "O" && board[i] != "X") {
            indexes.push_back(i);
        }
    }
    return indexes;
}

// winning combinations using the board indices
bool winning(const vector<string>& board, const string& player) {
    return ((board[0] == player && board[1] == player && board[2] == player) ||
            (board[3] == player && board[4] == player && board[5] == player) ||
            (board[6] == player && board[7] == player && board[8] == player) ||
            (board[0] == player && board[3] == player && board[6] == player) ||
            (board[1] == player && board[4] == player && board[7] == player) ||
            (board[2] == player && board[5] == player && board[8] == player) ||
            (board[0] == player && board[4] == player && board[8] == player) ||
            (board[2] == player && board[4] == player && board[6] == player));
}

// the main minimax function
struct Move {
    int index;
    int score;
};

Move minimax(vector<string>& newBoard, const string& player) {
    // available spots
    vector<int> availSpots = emptyIndexies(newBoard);

    // checks for the terminal states such as win, lose, and tie
    // and returning a value accordingly
    if (winning(newBoard, huPlayer)) {
        return {-1, -10};
    } else if (winning(newBoard, aiPlayer)) {
        return {-1, 10};
    } else if (availSpots.size() == 0) {
        return {-1, 0};
    }

    // an array to collect all the objects
    vector<Move> moves;

    // loop through available spots
    for (int i = 0; i < availSpots.size(); ++i) {
        // create an object for each and store the index of that spot
        Move move;
        move.index = availSpots[i];

        // set the empty spot to the current player
        newBoard[availSpots[i]] = player;

        /* collect the score resulted from calling minimax
           on the opponent of the current player */
        if (player == aiPlayer) {
            Move result = minimax(newBoard, huPlayer);
            move.score = result.score;
        } else {
            Move result = minimax(newBoard, aiPlayer);
            move.score = result.score;
        }

        // reset the spot to empty
        newBoard[availSpots[i]] = to_string(availSpots[i]);

        // push the object to the array
        moves.push_back(move);
    }

    // if it is the computer's turn loop over the moves and choose the move with
    // the highest score
    int bestMove = 0;
    if (player == aiPlayer) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < moves.size(); ++i) {
            if (moves[i].score > bestScore) {
                bestScore = moves[i].score;
                bestMove = i;
            }
        }
    } else {
        // else loop over the moves and choose the move with the lowest score
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < moves.size(); ++i) {
            if (moves[i].score < bestScore) {
                bestScore = moves[i].score;
                bestMove = i;
            }
        }
    }

    // return the chosen move (object) from the moves array
    return moves[bestMove];
}

// Print the Tic Tac Toe board
void printBoard(const vector<string>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i * 3 + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    vector<string> board = origBoard;
    int moves = 0;

    while (true) {
        // Human player's turn
        if (moves % 2 == 0) {
            int moveIndex;
            cout << "Human player's turn (O)." << endl;
            cout << "Enter the index (0-8) to place your move: ";
            cin >> moveIndex;
            if (moveIndex < 0 || moveIndex > 8 || board[moveIndex] != to_string(moveIndex)) {
                cout << "Invalid move! Try again." << endl;
                continue;
            }
            board[moveIndex] = huPlayer;
        }
        // AI player's turn
        else {
            cout << "AI player's turn (X)." << endl;
            Move bestMove = minimax(board, aiPlayer);
            board[bestMove.index] = aiPlayer;
        }

        // Print the current board
        printBoard(board);

        // Check for a win or draw
        if (winning(board, huPlayer)) {
            cout << "Human player (O) wins!" << endl;
            break;
        } else if (winning(board, aiPlayer)) {
            cout << "AI player (X) wins!" << endl;
            break;
        } else if (emptyIndexies(board).empty()) {
            cout << "It's a draw!" << endl;
            break;
        }

        // Increment moves counter
        ++moves;
    }

    return 0;
}
