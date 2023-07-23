#include "piece.h"

Piece::Piece(int row, int col, char name) {
  this->row = row;
  this->col = col;
  this->name = name;
  this->color = isupper(name) ? WHITE : BLACK;
  this->has_moved = false;
  this->potential_moves = {};
}

Piece::~Piece() {}

void Piece::getDiagonalMoves(vector<vector<Piece*>>& board, int row, int col,
                             vector<Move>& legal_moves) {
  // Check if piece can move up and right
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

  // Check if piece can move up and left
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

  // Check if piece can move down and right
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

  // Check if piece can move down and left
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

void Piece::getStraightMoves(vector<vector<Piece*>>& board, int row, int col,
                             vector<Move>& legal_moves) {
  // Check if piece can move up
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

  // Check if piece can move down
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

  // Check if piece can move left
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

  // Check if piece can move right
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

// Helper function to check if other piece is same color as this piece
bool Piece::isSameColor(Piece* other) {
  if (other == nullptr) {
    return false;
  }

  return this->color == other->getColor();
}

// Color offset so that white pieces move up and black pieces move down
int Piece::colorOffset() { return this->color == WHITE ? -1 : 1; }

// Given a row and column, if the move is in the list of potential moves,
// than it is a legal move. return true, else return false
bool Piece::isLegalMove(int row, int col) {
  for (const auto& move : this->potential_moves) {
    if (move.row == row && move.col == col) {
      return true;
    }
  }
  return false;
}

bool Piece::isPawn() {
  return this->getName() == 'p' || this->getName() == 'P';
}

bool Piece::isKing() {
  return this->getName() == 'k' || this->getName() == 'K';
}

vector<Move> Piece::getPathToKing(Piece* king) {
  vector<Move> path = {};

  // If the piece is a knight, return an empty path
  if (this->getName() == 'n' || this->getName() == 'N') {
    return path;
  }

  int dir_row;

  // Get the direction the king is in
  if (king->getRow() > this->getRow()) {
    dir_row = 1;
  } else if (king->getRow() < this->getRow()) {
    dir_row = -1;
  } else {
    dir_row = 0;
  }

  int dir_col;

  // Get the direction the king is in
  if (king->getCol() > this->getCol()) {
    dir_col = 1;
  } else if (king->getCol() < this->getCol()) {
    dir_col = -1;
  } else {
    dir_col = 0;
  }

  int curr_row = this->getRow();
  int curr_col = this->getCol();

  // Traverse path to the king
  while (curr_row != king->getRow() || curr_col != king->getCol()) {
    curr_row += dir_row;
    curr_col += dir_col;

    // Check if it is a valid move
    if (this->isLegalMove(curr_row, curr_col)) {
      path.push_back({curr_row, curr_col});
    }
  }

  return path;
}