#include "king.h"

// Constructor
King::King(int square, char piece) : Piece(square, piece) {
  this->is_in_check = false;
}

// Get the legal moves for the king
void King::updateLegalMoves(Piece* board[64]) {
  vector<int> legal_moves = {};

  this->checkPieceInPath(board, legal_moves);

  this->setLegalMoves(legal_moves);
}

void King::checkPieceInPath(Piece* board[64], vector<int>& legal_moves) {
  int directions[8] = {-9, -8, -7, -1, 1, 7, 8, 9};

  for (int offset : directions) {
    int square = this->getSquare() + offset;

    if (square >= 0 && square < 64 && abs(this->getCol() - square % 8) <= 1) {
      if (board[square] == nullptr) {
        legal_moves.push_back(square);
      } else if (board[square]->getColor() != this->getColor()) {
        legal_moves.push_back(square);
      }
    }
  }
}

void King::setCastlingSquare(Piece* board[64], int rook_square,
                             vector<Piece*>& pieces_attacking_king) {
  if (this->is_in_check) {
    return;
  }

  // If the rook is not on the starting square, return
  if (board[rook_square] == nullptr) {
    return;
  }

  // If a different piece is on the rook square, return
  if (!board[rook_square]->isRook()) {
    return;
  }

  // If the rook has moved, return
  if (board[rook_square]->getHasMoved()) {
    return;
  }

  // If the rook is not the same color as the king, return
  if (board[rook_square]->getColor() != this->getColor()) {
    return;
  }

  int direction = rook_square > this->getSquare() ? 1 : -1;
  int start = this->getSquare() + direction;
  int end = rook_square;

  for (int square = start; square != end; square += direction) {
    // If there is a piece in the way, return
    if (board[square] != nullptr) {
      return;
    }

    // Check if the king is moving through check
    if (this->isKingMovingThroughCheck(board, square, pieces_attacking_king)) {
      return;
    }
  }

  // Add the castling square to the legal moves
  vector<int> legal_moves = this->getLegalMoves();
  int castling_square = rook_square > this->getSquare() ? 2 : -2;
  legal_moves.push_back(this->getSquare() + castling_square);
  this->setLegalMoves(legal_moves);
}

bool King::isInCheck(Piece* board[64], vector<Piece*>& pieces,
                     vector<Piece*>& pieces_attacking_king) {
  // Check if the king is in check
  for (Piece* piece : pieces) {
    for (int square : piece->getLegalMoves()) {
      if (square == this->getSquare()) {
        pieces_attacking_king.push_back(piece);
        this->is_in_check = true;
        return true;
      }
    }
  }

  pieces_attacking_king = {};
  this->is_in_check = false;
  return false;
}

bool King::isKingMovingThroughCheck(Piece* board[64], int to_square,
                                    vector<Piece*> pieces_attacking_king) {
  vector<Piece*> pieces = {};

  // Get all the pieces of the opposite color
  for (int i = 0; i < 64; i++) {
    if (board[i] != nullptr && board[i]->getColor() != this->getColor()) {
      pieces.push_back(board[i]);
    }
  }

  int original_square = this->getSquare();

  // Check if the king is in check at the destination square
  board[to_square] = this;
  board[original_square] = nullptr;
  this->setSquare(to_square);

  bool is_in_check = this->isInCheck(board, pieces, pieces_attacking_king);

  // Reset the board
  board[original_square] = this;
  board[to_square] = nullptr;
  this->setSquare(original_square);

  return is_in_check;
}