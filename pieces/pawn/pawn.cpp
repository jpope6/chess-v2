#include "pawn.h"

// Constructor
Pawn::Pawn(int row, int col, char name) : Piece(row, col, name) {}

// TODO: FIX THIS
vector<Move> Pawn::updateLegalMoves(vector<vector<Piece*>> board) {
  vector<Move> legal_moves = {};
  int color_offset = this->colorOffset();

  int row = this->getRow();
  int col = this->getCol();

  // Check if pawn has moved
  int end_count = this->getHasMoved() ? 1 : 2;

  for (int i = 1; i <= end_count; i++) {
    if (row + i * color_offset < 0 || row + i * color_offset > 7) {
      break;
    }

    if (board[row + i * color_offset][col] == nullptr) {
      legal_moves.push_back({row + i * color_offset, col});
    } else {
      break;
    }
  }

  return legal_moves;
}