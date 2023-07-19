#ifndef PAWN_H
#define PAWN_H

#include <cmath>

#include "../piece.h"

class Pawn : public Piece {
 private:
 public:
  // Constructor and destructor
  Pawn(int row, int col, char name);
  ~Pawn();

  // Virtual Methods
  vector<Move> updateLegalMoves(vector<vector<Piece*>>& board) override;

  // Methods
  void checkPieceInPath(vector<vector<Piece*>>& board, int row, int col,
                        vector<Move>& legal_moves);
  void checkPawnCapture(vector<vector<Piece*>>& board, int row, int col,
                        vector<Move>& legal_moves);
  void updateEnPassant(vector<vector<Piece*>>& board, int row, int col);
};

#endif