#include "queen.h"

// Constructor
Queen::Queen(int row, int col, char name) : Piece(row, col, name) {}

// Returns all legal moves for the queen
vector<Move> Queen::updateLegalMoves(vector<vector<Piece*>>& board) {
  vector<Move> legal_moves = {};

  int row = this->getRow();
  int col = this->getCol();

  this->getDiagonalMoves(board, row, col, legal_moves);
  this->getStraightMoves(board, row, col, legal_moves);
  this->setPotentialMoves(legal_moves);

  return legal_moves;
}