#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"

class Bishop : public Piece {
 private:
 public:
  // Constructor
  Bishop(int quare, char piece);

  // Virtual functions
  void updateLegalMoves(Piece* board[64]) override;
};

#endif