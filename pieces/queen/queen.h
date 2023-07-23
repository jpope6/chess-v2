#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"

class Queen : public Piece {
 private:
 public:
  // Constructor and destructor
  Queen(int row, int col, char name);
  ~Queen();

  // Virtual Methods
  vector<Move> updateLegalMoves(vector<vector<Piece*>>& board) override;
};

#endif