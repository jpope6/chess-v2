#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece {
 private:
 public:
  // Constructor
  Pawn(int square, char piece);

  // Virtual functions
  void updateLegalMoves(Piece* board[64]) override;

  // Member functions
  void checkPieceInPath(Piece* board[64], vector<int>& legal_moves);
  void checkPieceInAttackPath(Piece* board[64], vector<int>& legal_moves);
  void addEnPassantSquare(int square);
};

#endif