#include "pawn.h"

// Constructor
Pawn::Pawn(int square, char piece) : Piece(square, piece) {}

// Get the legal moves for the pawn
void Pawn::updateLegalMoves(Piece* board[64]) {
  vector<int> legal_moves = {};

  this->checkPieceInPath(board, legal_moves);
  this->checkPieceInAttackPath(board, this->getSquare(), legal_moves);

  this->setLegalMoves(legal_moves);
}

// Check if there is a piece in the path of the pawn
void Pawn::checkPieceInPath(Piece* board[64], vector<int>& legal_moves) {
  // Pawn can move forward 1 square or 2 squares if it hasn't moved yet
  int directions[2] = {8, 16};
  int stop_index = this->getHasMoved() ? 1 : 2;

  // Pawns can only move in one direction
  int color_offset = this->getColor() == WHITE ? -1 : 1;

  for (int i = 0; i < stop_index; i++) {
    int square = this->getSquare() + directions[i] * color_offset;

    if (square >= 0 && square < 64) {
      if (board[square] == nullptr) {
        legal_moves.push_back(square);
      } else {
        break;
      }
    }
  }
}

// Check if there is a piece diagonally in front of the pawn
void Pawn::checkPieceInAttackPath(Piece* board[64], int square,
                                  vector<int>& legal_moves) {
  // Pawns can only move in one direction
  int color_offset = this->getColor() == WHITE ? -1 : 1;

  // Pawns can only capture diagonally
  int directions[2] = {7, 9};

  for (int i = 0; i < 2; i++) {
    int square = this->getSquare() + directions[i] * color_offset;

    if (square >= 0 && square < 64 && abs(this->getCol() - square % 8) <= 1) {
      if (board[square] != nullptr &&
          this->getColor() != board[square]->getColor()) {
        legal_moves.push_back(square);
      }
    }
  }
}

void Pawn::addEnPassantSquare(int square) {
  vector<int> legal_moves = this->getLegalMoves();
  legal_moves.push_back(square);
  this->setLegalMoves(legal_moves);
}