#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"

class Rook : public Piece {
 private:
 public:
  // Constructor
  Rook(int quare, char piece);

  // Virtual functions
  void updateLegalMoves(Piece* board[64]) override;
};

#endif