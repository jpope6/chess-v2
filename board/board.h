#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <string>

#include "../pieces/bishop/bishop.h"
#include "../pieces/king/king.h"
#include "../pieces/knight/knight.h"
#include "../pieces/pawn/pawn.h"
#include "../pieces/queen/queen.h"
#include "../pieces/rook/rook.h"

using namespace std;

struct Move {
  int from_square;
  int to_square;
};

class Board {
 private:
  string fen_string;
  Piece* board[64];

  Piece* white_king;
  Piece* black_king;

 public:
  // Constructor
  Board();

  // Getters
  string getFenString() { return fen_string; }
  Piece** getBoard() { return board; }

  // Member functions
  void setBoardWithFenString(string fen_string);
  Piece* createPiece(char c, int row, int col);
};

#endif
