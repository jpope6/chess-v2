#include "rook.h"

// Constructor
Rook::Rook(int square, char piece) : Piece(square, piece) {}

// Get the legal moves for the rook
void Rook::updateLegalMoves(Piece* board[64]) {
  vector<int> legal_moves = {};

  this->getStraightMoves(board, legal_moves);

  this->setLegalMoves(legal_moves);
}