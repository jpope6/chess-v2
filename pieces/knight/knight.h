#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"

class Knight : public Piece {
 private:
 public:
  // Constructor
  Knight(int quare, char piece);

  // Virtual functions
  void updateLegalMoves(Piece* board[64]) override;
};

#endif