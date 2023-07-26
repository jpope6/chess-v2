#ifndef KING_H
#define KING_H

#include "../piece.h"

class King : public Piece {
 private:
 public:
  // Constructor
  King(int square, char piece);

  // Virtual functions
  void updateLegalMoves(Piece* board[64]) override;

  // Member functions
  void checkCastlingRights(Piece* board[64], vector<int>& legal_moves);
};

#endif