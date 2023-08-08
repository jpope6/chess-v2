#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"

class Queen : public Piece {
 private:
 public:
  // Constructor
  Queen(int quare, char piece);

  // Virtual functions
  void updateLegalMoves(Piece* board[64]) override;
};

#endif