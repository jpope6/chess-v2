#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <string>
#include <vector>

#include "../pieces/bishop/bishop.h"
#include "../pieces/king/king.h"
#include "../pieces/knight/knight.h"
#include "../pieces/pawn/pawn.h"
#include "../pieces/queen/queen.h"
#include "../pieces/rook/rook.h"

using namespace std;

class Board {
 private:
  string fen_string;

 public:
  vector<vector<Piece*>> board;

  // Constructor and destructor
  Board();
  ~Board();

  // Getters
  string getFenString() { return fen_string; }

  // Member functions
  void setBoardWithFenString(string fen_string);
  void updateLegalMoves();
  bool movePiece(int from_row, int from_col, int to_row, int to_col);
};

#endif