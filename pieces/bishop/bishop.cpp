#include "bishop.h"

// Constructor
Bishop::Bishop(int row, int col, char name) : Piece(row, col, name) {}

// Returns all legal moves for the bishop
vector<Move> Bishop::updateLegalMoves(vector<vector<Piece*>>& board) {
  vector<Move> legal_moves = {};

  int row = this->getRow();
  int col = this->getCol();

  // Check if bishop can move forward
  this->getDiagonalMoves(board, row, col, legal_moves);
  this->setPotentialMoves(legal_moves);

  return legal_moves;
}