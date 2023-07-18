#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"

class Rook : public Piece {
 private:
 public:
  // Constructor and destructor
  Rook(int row, int col, char name);
  ~Rook();

  // Virtual Methods
  vector<Move> updateLegalMoves(vector<vector<Piece*>>& board) override;

  // Methods
  void checkPieceInPath(vector<vector<Piece*>>& board, int row, int col,
                        vector<Move>& legal_moves);
};

#endif