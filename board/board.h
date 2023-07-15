#ifndef BOARD_H
#define BOARD_H

#include <string>

using namespace std;

class Board {
 private:
  string fen_string;

 public:
  char board[8][8];

  // Constructor and destructor
  Board(/* args */);
  ~Board();

  // Getters
  string getFenString() { return fen_string; }

  // Member functions
  void setBoardWithFenString(string fen_string);
  bool movePiece(int from_row, int from_col, int to_row, int to_col);
};

#endif