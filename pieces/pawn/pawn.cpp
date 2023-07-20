#include "pawn.h"

// Constructor
Pawn::Pawn(int row, int col, char name) : Piece(row, col, name) {}

// Returns all legal moves for the pawn
vector<Move> Pawn::updateLegalMoves(vector<vector<Piece*>>& board) {
  int color_offset = this->colorOffset();

  int row = this->getRow();
  int col = this->getCol();

  vector<Move> legal_moves = {};

  // Check if pawn can move forward
  this->checkPieceInPath(board, row, col, legal_moves);

  // Check if pawn can capture
  this->checkPawnCapture(board, row, col, legal_moves);

  this->setPotentialMoves(legal_moves);

  return legal_moves;
}

// Helper function to check if there is a piece in the way of the pawn
void Pawn::checkPieceInPath(vector<vector<Piece*>>& board, int row, int col,
                            vector<Move>& legal_moves) {
  int color_offset = this->colorOffset();

  // Pawn can move 2 spaces if it hasn't moved yet
  // If it has moved, it can only move 1 space
  int end_count = this->getHasMoved() ? 1 : 2;

  for (int i = 1; i <= end_count; i++) {
    // Check if the move is in bounds
    if (row + i * color_offset < 0 || row + i * color_offset > 7) {
      break;
    }

    // If there is no piece in the way, add the move to the list of legal moves
    if (board[row + i * color_offset][col] == nullptr) {
      legal_moves.push_back({row + i * color_offset, col});
    } else {
      // There is a piece in the way, stop checking for legal moves in this
      // direction
      break;
    }
  }
}

// Helper function to check if pawn can capture
void Pawn::checkPawnCapture(vector<vector<Piece*>>& board, int row, int col,
                            vector<Move>& legal_moves) {
  int color_offset = this->colorOffset();

  // Offset the column and row by 1 to check if the pawn can capture
  int capture_offset[] = {-1, 1};

  for (int offset : capture_offset) {
    // Calculate the row and column of the capture
    int capture_row = row + color_offset;
    int capture_col = col + offset;

    // Check if the capture is in bounds
    if (capture_row < 0 || capture_row > 7 || capture_col < 0 ||
        capture_col > 7) {
      continue;
    }

    // Check if there is a piece to capture
    Piece* capture_piece = board[capture_row][capture_col];
    // If there is a piece and it is not the same color, add the move to the
    // list of legal moves
    if (capture_piece != nullptr && !this->isSameColor(capture_piece)) {
      legal_moves.push_back({capture_row, capture_col});
    }
  }
}

// TODO: Check if pawn can en passant
void Pawn::updateEnPassant(vector<vector<Piece*>>& board, int row, int col) {
  // Check if pawn is in the correct row
  if (this->getIsWhite() && this->getRow() != 3) {
    return;
  }

  if (this->getIsBlack() && this->getRow() != 4) {
    return;
  }

  // Check if on the right column
  if (abs(this->getCol() - col) != 1) {
    return;
  }

  int color_offset = this->colorOffset();

  // Check if this piece is the same color as the en passant square
  if (this->isSameColor(board[row + (1 * color_offset)][col])) {
    return;
  }

  // Add the move to the list of legal moves
  vector<Move>& legal_moves = this->getPotentialMoves();
  legal_moves.push_back({row, col});
}