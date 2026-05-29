#include <iostream>
#include <vector>
using namespace std;

class TicTacToe {
public:
    vector<char> board;

    TicTacToe() {
        board = vector<char>(9, ' ');
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

                return (board[w[0]] == 'X') ? 10 : -10;
            }
        }

        return 0;
    }

    int alphaBeta(bool isMax, int alpha, int beta) {
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

                    best = max(best, alphaBeta(false, alpha, beta));

                    board[i] = ' ';

                    alpha = max(alpha, best);

                    if (beta <= alpha)
                        break;
                }
            }

            return best;
        } else {
            int best = 1000;

            for (int i = 0; i < 9; i++) {
                if (board[i] == ' ') {
                    board[i] = 'O';

                    best = min(best, alphaBeta(true, alpha, beta));

                    board[i] = ' ';

                    beta = min(beta, best);

                    if (beta <= alpha)
                        break;
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

                int moveVal = alphaBeta(false, -1000, 1000);

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
        'X','O','X',
        'O','O',' ',
        'X',' ',' '
    };

    cout << "Best Move: " << game.findBestMove() << endl;

    return 0;
}
