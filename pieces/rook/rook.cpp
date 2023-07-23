#include "rook.h"

// Constructor
Rook::Rook(int row, int col, char name) : Piece(row, col, name) {}

// Returns all legal moves for the rook
vector<Move> Rook::updateLegalMoves(vector<vector<Piece*>>& board) {
  vector<Move> legal_moves = {};

  int row = this->getRow();
  int col = this->getCol();

  // Check if rook can move forward
  this->getStraightMoves(board, row, col, legal_moves);
  this->setPotentialMoves(legal_moves);

  return legal_moves;
}