#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"

class Bishop : public Piece {
 private:
 public:
  // Constructor and destructor
  Bishop(int row, int col, char name);
  ~Bishop();

  // Virtual Methods
  vector<Move> updateLegalMoves(vector<vector<Piece*>> board) override;

  // Methods
  void checkPieceInPath(vector<vector<Piece*>> board, int row, int col,
                        vector<Move>& legal_moves);
};

#endif