
#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <map>

using namespace std;

class Piece {
    private:
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
        
};

#endif