#include "bishop.h"

// Constructor
Bishop::Bishop(int square, char piece) : Piece(square, piece) {}

// Get the legal moves for the bishop
void Bishop::updateLegalMoves(Piece* board[64]) {
  vector<int> legal_moves = {};

  this->getDiagonalMoves(board, legal_moves);

  this->setLegalMoves(legal_moves);
}