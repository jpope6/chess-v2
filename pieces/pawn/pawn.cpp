#include "pawn.h"

// Constructor
Pawn::Pawn(int row, int col, char name) : Piece(row, col, name) {}

// Returns all legal moves for the pawn
vector<Move> Pawn::updateLegalMoves(vector<vector<Piece*>> board) {
  vector<Move> legal_moves = {};
  int color_offset = this->colorOffset();

  int row = this->getRow();
  int col = this->getCol();

  // Check if pawn can move forward
  this->checkPieceInPath(board, row, col, legal_moves);

  // Check if pawn can capture
  this->checkPawnCapture(board, row, col, legal_moves);

  return legal_moves;
}

// Helper function to check if there is a piece in the way of the pawn
void Pawn::checkPieceInPath(vector<vector<Piece*>> board, int row, int col,
                            vector<Move>& legal_moves) {
  int color_offset = this->colorOffset();

  // Check if pawn has moved
  int end_count = this->getHasMoved() ? 1 : 2;

  for (int i = 1; i <= end_count; i++) {
    // check if move is in bounds
    if (row + i * color_offset < 0 || row + i * color_offset > 7) {
      break;
    }

    // check if nothing is in the way
    if (board[row + i * color_offset][col] == nullptr) {
      legal_moves.push_back({row + i * color_offset, col});
    } else {
      // there is a piece in the way, so stop checking
      break;
    }
  }
}

// Helper function to check if pawn can capture
void Pawn::checkPawnCapture(vector<vector<Piece*>> board, int row, int col,
                            vector<Move>& legal_moves) {
  int color_offset = this->colorOffset();

  // Check if pawn can capture
  int capture_offset[] = {-1, 1};

  for (int offset : capture_offset) {
    int capture_row = row + color_offset;
    int capture_col = col + offset;

    // check if capture is in bounds
    if (capture_row < 0 || capture_row > 7 || capture_col < 0 ||
        capture_col > 7) {
      continue;
    }

    // check if capture is valid
    Piece* capture_piece = board[capture_row][capture_col];
    if (capture_piece != nullptr && !this->isSameColor(capture_piece)) {
      legal_moves.push_back({capture_row, capture_col});
    }
  }
}