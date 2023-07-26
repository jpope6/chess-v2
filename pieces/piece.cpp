#include "piece.h"

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
  int directions[4] = {-9, -7, 7, 9};

  for (int offset : directions) {
    int square = this->square + offset;

    while (square >= 0 && square < 64) {
      // If piece is the same color, break
      if (board[square] != nullptr &&
          this->color == board[square]->getColor()) {
        break;
      }

      // If piece is of the opposite color, add the square and break
      if (board[square] != nullptr &&
          this->color != board[square]->getColor()) {
        legal_moves.push_back(square);
        break;
      }

      // If the square is empty, add it and continue to the next square on the
      // diagonal
      legal_moves.push_back(square);

      // If the square is on the edge of the board, break
      if (square % 8 == 0 || square % 8 == 7) {
        break;
      }

      square += offset;
    }
  }
}

void Piece::getStraightMoves(Piece* board[64], vector<int>& legal_moves) {
  int directions[4] = {-8, -1, 1, 8};

  for (int offset : directions) {
    int square = this->square + offset;

    while (square % 8 != 0 && square % 8 != 7) {
      // If piece is the same color, break
      if (board[square] != nullptr &&
          this->color == board[square]->getColor()) {
        break;
      }

      // If piece is of the opposite color, add the square and break
      if (board[square] != nullptr &&
          this->color != board[square]->getColor()) {
        legal_moves.push_back(square);
        break;
      }

      // If the square is empty, add it and continue to the next square on the
      // diagonal
      legal_moves.push_back(square);

      square += offset;
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