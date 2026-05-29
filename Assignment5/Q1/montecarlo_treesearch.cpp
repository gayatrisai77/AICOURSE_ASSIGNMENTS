#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class TicTacToe {
public:
    vector<char> board;

    TicTacToe() {
        board = vector<char>(9, ' ');
    }

    vector<int> getMoves() {
        vector<int> moves;

        for (int i = 0; i < 9; i++)
            if (board[i] == ' ')
                moves.push_back(i);

        return moves;
    }

    int checkWinner() {
        int wins[8][3] = {
            {0,1,2},{3,4,5},{6,7,8},
            {0,3,6},{1,4,7},{2,5,8},
            {0,4,8},{2,4,6}
        };

        for (auto &w : wins) {
            if (board[w[0]] == board[w[1]] &&
                board[w[1]] == board[w[2]] &&
                board[w[0]] != ' ') {

                return board[w[0]] == 'X' ? 1 : -1;
            }
        }

        return 0;
    }

    int randomPlayout(char player) {
        int winner = checkWinner();

        if (winner != 0)
            return winner;

        vector<int> moves = getMoves();

        if (moves.empty())
            return 0;

        int move = moves[rand() % moves.size()];

        board[move] = player;

        int result =
            randomPlayout(player == 'X' ? 'O' : 'X');

        board[move] = ' ';

        return result;
    }

    int findBestMove(int simulations) {
        vector<int> moves = getMoves();

        int bestMove = -1;
        int bestScore = -100000;

        for (int move : moves) {
            int score = 0;

            for (int i = 0; i < simulations; i++) {
                board[move] = 'X';

                score += randomPlayout('O');

                board[move] = ' ';
            }

            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }

        return bestMove;
    }
};

int main() {
    srand(time(0));

    TicTacToe game;

    game.board = {
        'X','O',' ',
        ' ','X',' ',
        'O',' ',' '
    };

    int move = game.findBestMove(1000);

    cout << "Best Move using MCTS: " << move << endl;

    return 0;
}
