#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <map>
#include <fstream>

using namespace std;

class Board {
    private:
        // FEN string for the starting position
        string fen_string;
        bool isGameOver;
        // map<char, string> piece_art = {
        //     {'P', "♝"},
        //     {'N', "♞"},
        //     {'B', "♝"},
        //     {'R', "♜"},
        //     {'Q', "♛"},
        //     {'K', "♚"},
        //     {'p', "♙"},
        //     {'n', "♘"},
        //     {'b', "♗"},
        //     {'r', "♖"},
        //     {'q', "♕"},
        //     {'k', "♔"},
        //     {' ', "-"}
        // };

    public:
        // 2D array to represent the board
        string board[8][8] = {};

        // Board constructor
        Board();

        // Getters
        string getFenString() { return fen_string; }
        bool getIsGameOver() { return isGameOver; }
        // map<char, string> getPieceArt() { return piece_art; }

        // Setters
        void setIsGameOver(bool isGameOver) { this->isGameOver = isGameOver; }

        void setBoardWithFenString(string fen_string);
        void writeFenStringToFile(string fen_string);
        void printBoard();
};

#endif