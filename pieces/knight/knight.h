#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"

class Knight : public Piece {
 private:
 public:
  // Constructor and destructor
  Knight(int row, int col, char name);
  ~Knight();

  // Virtual Methods
  vector<Move> updateLegalMoves(vector<vector<Piece*>>& board) override;

  // Methods
  void checkPieceInPath(vector<vector<Piece*>> board, int row, int col,
                        vector<Move>& legal_moves);
};

#endif