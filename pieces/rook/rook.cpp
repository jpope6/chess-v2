#include "rook.h"

// Constructor
Rook::Rook(int row, int col, char name) : Piece(row, col, name) {}

// Returns all legal moves for the rook
vector<Move> Rook::updateLegalMoves(vector<vector<Piece*>> board) {
  vector<Move> legal_moves = {};

  int row = this->getRow();
  int col = this->getCol();

  // Check if rook can move forward
  this->checkPieceInPath(board, row, col, legal_moves);

  return legal_moves;
}

// Helper function to check if there is a piece in the way of the rook
void Rook::checkPieceInPath(vector<vector<Piece*>> board, int row, int col,
                            vector<Move>& legal_moves) {
  // Check if rook can move up
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

  // Check if rook can move down
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

  // Check if rook can move left
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

  // Check if rook can move right
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
}