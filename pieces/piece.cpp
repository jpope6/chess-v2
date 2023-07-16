#include "piece.h"

Piece::Piece(int row, int col, char name) {
  this->row = row;
  this->col = col;
  this->name = name;
  this->is_white = isupper(name);
  this->has_moved = false;
  this->potential_moves = {};
}

Piece::~Piece() {}

// Helper function to check if other piece is same color as this piece
bool Piece::isSameColor(Piece* other) {
  return this->is_white == other->getIsWhite();
}

// Color offset so that white pieces move up and black pieces move down
int Piece::colorOffset() { return this->is_white ? -1 : 1; }