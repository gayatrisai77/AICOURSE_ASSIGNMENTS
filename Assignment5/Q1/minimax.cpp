#include <iostream>
#include <vector>
using namespace std;

class TicTacToe {
public:
    vector<char> board;

    TicTacToe() {
        board = vector<char>(9, ' ');
    }

    void printBoard() {
        cout << "\n";
        for (int i = 0; i < 9; i++) {
            cout << (board[i] == ' ' ? char('0' + i) : board[i]);

            if ((i + 1) % 3 == 0)
                cout << "\n";
            else
                cout << " | ";
        }
        cout << "\n";
    }

    bool isMovesLeft() {
        for (char c : board)
            if (c == ' ')
                return true;
        return false;
    }

    int evaluate() {
        int wins[8][3] = {
            {0,1,2},{3,4,5},{6,7,8},
            {0,3,6},{1,4,7},{2,5,8},
            {0,4,8},{2,4,6}
        };

        for (auto &w : wins) {
            if (board[w[0]] == board[w[1]] &&
                board[w[1]] == board[w[2]] &&
                board[w[0]] != ' ') {

                if (board[w[0]] == 'X')
                    return 10;
                else
                    return -10;
            }
        }
        return 0;
    }

    int minimax(bool isMax) {
        int score = evaluate();

        if (score == 10 || score == -10)
            return score;

        if (!isMovesLeft())
            return 0;

        if (isMax) {
            int best = -1000;

            for (int i = 0; i < 9; i++) {
                if (board[i] == ' ') {
                    board[i] = 'X';
                    best = max(best, minimax(false));
                    board[i] = ' ';
                }
            }
            return best;
        } else {
            int best = 1000;

            for (int i = 0; i < 9; i++) {
                if (board[i] == ' ') {
                    board[i] = 'O';
                    best = min(best, minimax(true));
                    board[i] = ' ';
                }
            }
            return best;
        }
    }

    int findBestMove() {
        int bestVal = -1000;
        int bestMove = -1;

        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';

                int moveVal = minimax(false);

                board[i] = ' ';

                if (moveVal > bestVal) {
                    bestMove = i;
                    bestVal = moveVal;
                }
            }
        }

        return bestMove;
    }
};

int main() {
    TicTacToe game;

    game.board = {
        'X', 'O', 'X',
        'O', 'O', ' ',
        'X', ' ', ' '
    };

    game.printBoard();

    int bestMove = game.findBestMove();

    cout << "Best Move for X: " << bestMove << endl;

    return 0;
}
