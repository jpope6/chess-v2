#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <stack>
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
  Piece* piece;
  Piece* captured_piece;
};

class Board {
 private:
  string fen_string;
  Piece* board[64];

  stack<Move> move_stack;

  Color turn;

  King* white_king;
  King* black_king;

 public:
  // Constructor
  Board();

  // Getters
  string getFenString() { return fen_string; }
  Piece** getBoard() { return board; }
  stack<Move> getMoveStack() { return move_stack; }
  Color getTurn() { return turn; }

  // Member functions
  void setBoardWithFenString(string fen_string);
  Piece* createPiece(int square, char c);
  void handleMove(int from_square, int to_square);
  void updateMovesForAllPiecesOfCurrentTurn();
  void changeTurn();
  void addMoveToStack(Move move) { this->move_stack.push(move); }
  void setEnPassantSquare();
  void handleEnPassantCapture();
  void handleCastlingRights();
  void moveRookOnCastle();
};

#endif
