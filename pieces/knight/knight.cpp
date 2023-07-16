#include "knight.h"

// Constructor
Knight::Knight(int row, int col, char name) : Piece(row, col, name) {}

// Returns all legal moves for the pawn
vector<Move> Knight::updateLegalMoves(vector<vector<Piece*>> board) {
  vector<Move> legal_moves = {};

  int row = this->getRow();
  int col = this->getCol();

  // Check if pawn can move forward
  this->checkPieceInPath(board, row, col, legal_moves);

  return legal_moves;
}

// Helper function to check if there is a piece in the way of the pawn
void Knight::checkPieceInPath(vector<vector<Piece*>> board, int row, int col,
                              vector<Move>& legal_moves) {
  // knight offsets
  int offsets[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                       {1, -2},  {1, 2},  {2, -1},  {2, 1}};

  for (const auto& offset : offsets) {
    int new_row = row + offset[0];
    int new_col = col + offset[1];

    if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
      if (board[new_row][new_col] == nullptr) {
        legal_moves.push_back({new_row, new_col});
      } else {
        if (!this->isSameColor(board[new_row][new_col])) {
          legal_moves.push_back({new_row, new_col});
        }
      }
    }
  }
}
