#include "bishop.h"

// Constructor
Bishop::Bishop(int row, int col, char name) : Piece(row, col, name) {}

// Returns all legal moves for the bishop
vector<Move> Bishop::updateLegalMoves(vector<vector<Piece*>>& board) {
  vector<Move> legal_moves = {};

  int row = this->getRow();
  int col = this->getCol();

  // Check if bishop can move forward
  this->checkPieceInPath(board, row, col, legal_moves);
  this->setPotentialMoves(legal_moves);

  return legal_moves;
}

// Helper function to check if there is a piece in the way of the bishop
void Bishop::checkPieceInPath(vector<vector<Piece*>> board, int row, int col,
                              vector<Move>& legal_moves) {
  // Check if bishop can move up and right
  for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++) {
    // If there is no piece in the way, add the move to the list of legal moves
    if (board[i][j] == nullptr) {
      legal_moves.push_back({i, j});
    } else {  // If there is a piece in the way
      // if the piece is a different color, add the move to the list of legal
      if (!this->isSameColor(board[i][j])) {
        legal_moves.push_back({i, j});
      }
      // stop checking for legal moves in this direction
      break;
    }
  }

  // The same logic repeats for the other every other direction

  // Check if bishop can move up and left
  for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) {
    if (board[i][j] == nullptr) {
      legal_moves.push_back({i, j});
    } else {
      if (!this->isSameColor(board[i][j])) {
        legal_moves.push_back({i, j});
      }
      break;
    }
  }

  // Check if bishop can move down and right
  for (int i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++) {
    if (board[i][j] == nullptr) {
      legal_moves.push_back({i, j});
    } else {
      if (!this->isSameColor(board[i][j])) {
        legal_moves.push_back({i, j});
      }
      break;
    }
  }

  // Check if bishop can move down and left
  for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
    if (board[i][j] == nullptr) {
      legal_moves.push_back({i, j});
    } else {
      if (!this->isSameColor(board[i][j])) {
        legal_moves.push_back({i, j});
      }
      break;
    }
  }
}
