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
  if (other == nullptr) {
    return false;
  }

  return this->is_white == other->getIsWhite();
}

// Color offset so that white pieces move up and black pieces move down
int Piece::colorOffset() { return this->is_white ? -1 : 1; }

// Given a row and column, if the move is in the list of potential moves,
// than it is a legal move. return true, else return false
bool Piece::isLegalMove(int row, int col) {
  for (const auto& move : this->potential_moves) {
    if (move.row == row && move.col == col) {
      return true;
    }
  }
  return false;
}

bool Piece::isPawn() {
  return this->getName() == 'p' || this->getName() == 'P';
}