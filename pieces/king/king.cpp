#include "king.h"

// Constructor
King::King(int square, char piece) : Piece(square, piece) {}

// Get the legal moves for the king
void King::updateLegalMoves(Piece* board[64]) {
  vector<int> legal_moves = {};

  int directions[8] = {-9, -8, -7, -1, 1, 7, 8, 9};

  for (int offset : directions) {
    int square = this->getSquare() + offset;

    if (square >= 0 && square < 64) {
      if (board[square] == nullptr) {
        legal_moves.push_back(square);
      } else if (board[square]->getColor() != this->getColor()) {
        legal_moves.push_back(square);
      }
    }
  }

  this->setLegalMoves(legal_moves);
}