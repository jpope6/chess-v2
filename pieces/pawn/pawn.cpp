#include "pawn.h"

// Constructor
Pawn::Pawn(int square, char piece) : Piece(square, piece) {}

// Get the legal moves for the pawn
void Pawn::updateLegalMoves(Piece* board[64]) {
  vector<int> legal_moves = {};

  // Pawn can move forward 1 square or 2 squares if it hasn't moved yet
  int directions[2] = {8, 16};
  int stop_index = this->getHasMoved() ? 1 : 2;

  // Pawns can only move in one direction
  int color_offset = this->getColor() == WHITE ? -1 : 1;

  for (int i = 0; i < stop_index; i++) {
    int square = this->getSquare() + directions[i] * color_offset;

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