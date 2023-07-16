#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece {
 private:
 public:
  // Constructor and destructor
  Pawn(int row, int col, char name);
  ~Pawn();

  // Virtual Methods
  vector<Move> updateLegalMoves(vector<vector<Piece*>> board) override;
};

#endif