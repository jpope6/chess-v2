#include "pawn.h"

// Constructor
Pawn::Pawn(int square, char piece) : Piece(square, piece) {}

// Get the legal moves for the pawn
void Pawn::updateLegalMoves(Piece* board[64]) {
  vector<int> legal_moves = {};

  int directions[2] = {8, 16};
  int color_offset = this->getColor() == WHITE ? -1 : 1;

  for (int offset : directions) {
    int square = this->getSquare() + offset * color_offset;

    if (square >= 0 && square < 64) {
      if (board[square] == nullptr) {
        legal_moves.push_back(square);
      } else {
        break;
      }
    }
  }

  this->setLegalMoves(legal_moves);
}