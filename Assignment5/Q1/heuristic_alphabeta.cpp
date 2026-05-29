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

    int heuristic() {
        int score = 0;

        int wins[8][3] = {
            {0,1,2},{3,4,5},{6,7,8},
            {0,3,6},{1,4,7},{2,5,8},
            {0,4,8},{2,4,6}
        };

        for (auto &w : wins) {
            int xCount = 0, oCount = 0;

            for (int i = 0; i < 3; i++) {
                if (board[w[i]] == 'X') xCount++;
                if (board[w[i]] == 'O') oCount++;
            }

            if (xCount > 0 && oCount == 0)
                score += xCount;

            if (oCount > 0 && xCount == 0)
                score -= oCount;
        }

        return score;
    }

    int alphaBeta(int depth, bool isMax, int alpha, int beta) {
        if (depth == 0 || !isMovesLeft())
            return heuristic();

        if (isMax) {
            int best = -1000;

            for (int i = 0; i < 9; i++) {
                if (board[i] == ' ') {
                    board[i] = 'X';

                    best = max(best,
                               alphaBeta(depth - 1, false, alpha, beta));

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

                    best = min(best,
                               alphaBeta(depth - 1, true, alpha, beta));

                    board[i] = ' ';

                    beta = min(beta, best);

                    if (beta <= alpha)
                        break;
                }
            }

            return best;
        }
    }

    int findBestMove(int depth) {
        int bestVal = -1000;
        int bestMove = -1;

        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';

                int moveVal =
                    alphaBeta(depth - 1, false, -1000, 1000);

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
        'X','O',' ',
        ' ','X',' ',
        'O',' ',' '
    };

    int bestMove = game.findBestMove(4);

    cout << "Best Move: " << bestMove << endl;

    return 0;
}
