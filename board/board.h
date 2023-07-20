#ifndef BOARD_H
#define BOARD_H

#include <stack>
#include <string>
#include <vector>

#include "../pieces/bishop/bishop.h"
#include "../pieces/king/king.h"
#include "../pieces/knight/knight.h"
#include "../pieces/pawn/pawn.h"
#include "../pieces/queen/queen.h"
#include "../pieces/rook/rook.h"

using namespace std;

struct ChessMove {
  int from_row;
  int from_col;
  int to_row;
  int to_col;
  Piece* piece;
};

class Board {
 private:
  string fen_string;
  stack<ChessMove> move_stack;
  int en_passant_row;
  int en_passant_col;

 public:
  vector<vector<Piece*>> board;

  // Constructor and destructor
  Board();
  ~Board();

  // Getters
  string getFenString() { return fen_string; }
  ChessMove getLastMove() { return move_stack.top(); }
  int getEnPassantRow() { return en_passant_row; }
  int getEnPassantCol() { return en_passant_col; }

  // Member functions
  void setBoardWithFenString(string fen_string);
  Piece* createPiece(char c, int row, int col);
  bool movePiece(int from_row, int from_col, int to_row, int to_col);
  void handleMove(int from_row, int from_col, int to_row, int to_col);
  void addMoveToStack(int from_row, int from_col, int to_row, int to_col,
                      Piece* piece);
  bool setEnPassantSquare();
  void removeEnPassantPiece();
};

#endif