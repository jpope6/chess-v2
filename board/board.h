#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <string>
#include <vector>

#include "../pieces/pawn/pawn.h"

using namespace std;

class Board {
 private:
  string fen_string;

 public:
  vector<vector<Piece*>> board;

  // Constructor and destructor
  Board(/* args */);
  ~Board();

  // Getters
  string getFenString() { return fen_string; }

  // Member functions
  void setBoardWithFenString(string fen_string);
  void setLegalMoves();
  bool movePiece(int from_row, int from_col, int to_row, int to_col);
};

#endif