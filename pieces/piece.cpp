#include "piece.h"

#include <iostream>

Piece::Piece(int square, char piece) {
  this->row = square / 8;
  this->col = square % 8;
  this->square = square;
  this->name = piece;
  this->color = isupper(piece) ? WHITE : BLACK;

  piece = toupper(piece);
  map<char, Type> piece_type_map = {{'P', PAWN}, {'N', KNIGHT}, {'B', BISHOP},
                                    {'R', ROOK}, {'Q', QUEEN},  {'K', KING}};
  this->piece_type = piece_type_map[piece];

  this->has_moved = false;
}

void Piece::getDiagonalMoves(Piece* board[64], vector<int>& legal_moves) {
  // The offset from the current square to the next square on the diagonal
  int directions[4] = {-9, -7, 7, 9};

  // The number of squares until the edge of the board in each direction
  int squares_until_edge[4] = {
      min(this->row, this->col), min(this->row, 7 - this->col),
      min(7 - this->row, this->col), min(7 - this->row, 7 - this->col)};

  for (int i = 0; i < 4; i++) {  // For each direction
    int square = this->square;   // Start at the current square
    for (int j = 0; j < squares_until_edge[i]; j++) {  // For each square
      // Move to the next square on the diagonal
      square += directions[i];

      // If piece is the same color, stop looking in this direction
      if (board[square] != nullptr &&
          this->color == board[square]->getColor()) {
        break;
      }

      // If the square is empty or of the opposite color, add it and continue to
      // the next square on the diagonal
      legal_moves.push_back(square);

      // If piece is of the opposite color, stop looking in this direction
      if (board[square] != nullptr &&
          this->color != board[square]->getColor()) {
        break;
      }
    }
  }
}

void Piece::getStraightMoves(Piece* board[64], vector<int>& legal_moves) {
  // The offset from the current square to the next square in each direction
  int directions[4] = {-8, 1, 8, -1};  // Up, Right, Down, Left

  // The number of squares until the edge of the board in each direction
  int squares_until_edge[4] = {this->row, 7 - this->col, 7 - this->row,
                               this->col};

  for (int i = 0; i < 4; i++) {  // For each direction
    int square = this->square;   // Start at the current square
    for (int j = 0; j < squares_until_edge[i]; j++) {  // For each square
      // Move to the next square in the direction
      square += directions[i];

      // If piece is the same color, stop looking in this direction
      if (board[square] != nullptr &&
          this->color == board[square]->getColor()) {
        break;
      }

      // If the square is empty or of the opposite color, add it and continue to
      // the next square in the direction
      legal_moves.push_back(square);

      // If piece is of the opposite color, stop looking in this direction
      if (board[square] != nullptr &&
          this->color != board[square]->getColor()) {
        break;
      }
    }
  }
}

bool Piece::isLegalMove(int square) {
  for (int move : this->legal_moves) {
    if (move == square) {
      return true;
    }
  }

  return false;
}