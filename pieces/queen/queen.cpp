#include "queen.h"

// Constructor
Queen::Queen(int row, int col, char name) : Piece(row, col, name) {}

// Returns all legal moves for the queen
vector<Move> Queen::updateLegalMoves(vector<vector<Piece*>> board) {
  vector<Move> legal_moves = {};

  int row = this->getRow();
  int col = this->getCol();

  // Check if queen can move forward
  this->checkPieceInPath(board, row, col, legal_moves);

  return legal_moves;
}

// Helper function to check if there is a piece in the way of the queen
void Queen::checkPieceInPath(vector<vector<Piece*>> board, int row, int col,
                             vector<Move>& legal_moves) {
  // Check if queen can move up
  for (int i = row + 1; i < 8; i++) {
    // If there is no piece in the way, add the move to the list of legal moves
    if (board[i][col] == nullptr) {
      legal_moves.push_back({i, col});
    } else {  // If there is a piece in the way
      // if the piece is a different color, add the move to the list of legal
      // then stop checking for legal moves in this direction
      if (!this->isSameColor(board[i][col])) {
        legal_moves.push_back({i, col});
      }
      // if the piece is the same color, stop checking for legal moves in this
      // direction
      break;
    }
  }

  // The same logic repeats for the other every other direction

  // Check if queen can move down
  for (int i = row - 1; i >= 0; i--) {
    if (board[i][col] == nullptr) {
      legal_moves.push_back({i, col});
    } else {
      if (!this->isSameColor(board[i][col])) {
        legal_moves.push_back({i, col});
      }
      break;
    }
  }

  // Check if queen can move left
  for (int i = col - 1; i >= 0; i--) {
    if (board[row][i] == nullptr) {
      legal_moves.push_back({row, i});
    } else {
      if (!this->isSameColor(board[row][i])) {
        legal_moves.push_back({row, i});
      }
      break;
    }
  }

  // Check if queen can move right
  for (int i = col + 1; i < 8; i++) {
    if (board[row][i] == nullptr) {
      legal_moves.push_back({row, i});
    } else {
      if (!this->isSameColor(board[row][i])) {
        legal_moves.push_back({row, i});
      }
      break;
    }
  }

  // Check if queen can move up and right
  for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++) {
    if (board[i][j] == nullptr) {
      legal_moves.push_back({i, j});
    } else {
      if (!this->isSameColor(board[i][j])) {
        legal_moves.push_back({i, j});
      }
      break;
    }
  }

  // Check if queen can move up and left
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

  // Check if queen can move down and right
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

  // Check if queen can move down and left
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