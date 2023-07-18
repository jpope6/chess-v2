#include "knight.h"

// Constructor
Knight::Knight(int row, int col, char name) : Piece(row, col, name) {}

// Returns all legal moves for the knight
vector<Move> Knight::updateLegalMoves(vector<vector<Piece*>>& board) {
  vector<Move> legal_moves = {};

  int row = this->getRow();
  int col = this->getCol();

  // Check if knight can move forward
  this->checkPieceInPath(board, row, col, legal_moves);
  this->setPotentialMoves(legal_moves);

  return legal_moves;
}

// Helper function to check if there is a piece in the way of the knight
void Knight::checkPieceInPath(vector<vector<Piece*>>& board, int row, int col,
                              vector<Move>& legal_moves) {
  // Knights can move 2 spaces in one direction and 1 space in the other
  int offsets[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                       {1, -2},  {1, 2},  {2, -1},  {2, 1}};

  for (const auto& offset : offsets) {
    // Calculate the row and column of the new move
    int new_row = row + offset[0];
    int new_col = col + offset[1];

    // If the new move is in bounds
    if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
      // If there is no piece in the way, add the move to the list of legal
      // moves
      if (board[new_row][new_col] == nullptr) {
        legal_moves.push_back({new_row, new_col});
      } else {
        // There is a piece in the way, check if it is the same color
        // If it is not the same color, add the move to the list of legal moves
        if (!this->isSameColor(board[new_row][new_col])) {
          legal_moves.push_back({new_row, new_col});
        }
      }
    }
  }
}
