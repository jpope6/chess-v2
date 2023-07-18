#ifndef KING_H
#define KING_H

#include "../piece.h"

class King : public Piece {
 private:
 public:
  // Constructor and destructor
  King(int row, int col, char name);
  ~King();

  // Virtual Methods
  vector<Move> updateLegalMoves(vector<vector<Piece*>>& board) override;

  // Methods
  void checkPieceInPath(vector<vector<Piece*>>& board, int row, int col,
                        vector<Move>& legal_moves);
};

#endif