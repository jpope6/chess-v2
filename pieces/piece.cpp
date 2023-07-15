#include "piece.h"

Piece::Piece(int row, int col, char name, bool is_white) {
  this->row = row;
  this->col = col;
  this->name = name;
  this->is_white = is_white;
  this->potential_moves = {};
  this->legal_moves = {};
}

Piece::~Piece() {}

// Helper function to check if other piece is same color as this piece
bool Piece::isSameColor(Piece* other) {
  return this->is_white == other->getIsWhite();
}