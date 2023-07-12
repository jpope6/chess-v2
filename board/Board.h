#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <map>

using namespace std;

class Board {
    private:
        // FEN string for the starting position
        string fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        map<char, string> piece_art = {
            {'P', "♝"},
            {'N', "♞"},
            {'B', "♝"},
            {'R', "♜"},
            {'Q', "♛"},
            {'K', "♚"},
            {'p', "♙"},
            {'n', "♘"},
            {'b', "♗"},
            {'r', "♖"},
            {'q', "♕"},
            {'k', "♔"},
            {' ', "-"}
        };

    public:
        // 2D array to represent the board
        string board[8][8] = {};

        // Board constructor
        Board();

        // Getters
        string getFenString() { return fen_string; }
        map<char, string> getPieceArt() { return piece_art; }

        void setBoardWithFenString(string fen_string);
        void printBoard();
};

#endif