#include "knight.h"

// Constructor
Knight::Knight(int square, char piece) : Piece(square, piece) {}

// Get the legal moves for the knight
void Knight::updateLegalMoves(Piece* board[64]) {
  vector<int> legal_moves = {};

  int directions[8] = {-17, -15, -10, -6, 6, 10, 15, 17};

  for (int offset : directions) {
    int square = this->getSquare() + offset;

    // If the square is on the board and is within 2 columns of the current
    // square
    if (square >= 0 && square < 64 && abs(this->getCol() - square % 8) < 3) {
      if (board[square] == nullptr ||
          board[square]->getColor() != this->getColor()) {
        legal_moves.push_back(square);
      }
    }
  }

  this->setLegalMoves(legal_moves);
}