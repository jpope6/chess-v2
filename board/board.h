#ifndef BOARD_H
#define BOARD_H

#include <string>

using namespace std;

class Board {
    private:
        /* data */
        string fen_string;
    public:
        char board[8][8];

        Board(/* args */);
        ~Board();

        // Getters
        string getFenString() { return fen_string; }

        void setBoardWithFenString(string fen_string);
        void movePiece(int from_row, int from_col, int to_row, int to_col);
    };

#endif