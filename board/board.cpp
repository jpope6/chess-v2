#include "board.h"

#include <iostream>

Board::Board() {
  fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

  // Set the starting board
  setBoardWithFenString(fen_string);
  updateMovesForAllPieces();
}

// Set the board with the FEN string
void Board::setBoardWithFenString(string fen_string) {
  for (int i = 0; i < 64; i++) {
    board[i] = nullptr;
  }

  // Get the board part of the FEN string
  string fen_board = fen_string.substr(0, fen_string.find(" "));

  int row = 0;
  int col = 0;

  // Loop through the FEN board string
  for (char c : fen_board) {
    if (c == '/') {  // If we reach the end of a row
      row++;
      col = 0;
    } else {
      if (isdigit(c)) {  // If the character is a number
        int num = c - '0';
        col += num;
      } else {
        board[row * 8 + col] = createPiece(row * 8 + col, c);
        col++;
      }
    }
  }
}

// Create a piece based on the character
Piece* Board::createPiece(int square, char c) {
  switch (c) {
    case 'P':
    case 'p':
      return new Pawn(square, c);
    case 'R':
    case 'r':
      return new Rook(square, c);
    case 'B':
    case 'b':
      return new Bishop(square, c);
    case 'N':
    case 'n':
      return new Knight(square, c);
    case 'Q':
    case 'q':
      return new Queen(square, c);
    case 'K':
      white_king = new King(square, c);
      return white_king;
    case 'k':
      black_king = new King(square, c);
      return black_king;
    default:
      return nullptr;  // Invalid piece character
  }
}

void Board::handleMove(int from_square, int to_square) {
  // Create a new move
  Move move;
  move.from_square = from_square;
  move.to_square = to_square;
  move.piece = board[from_square];

  if (!move.piece->isLegalMove(to_square)) {
    return;
  }

  // Move the piece
  if (board[to_square] != nullptr) {
    delete board[to_square];
  }

  board[to_square] = move.piece;
  board[from_square] = nullptr;

  // Update the piece's square
  move.piece->setSquare(to_square);

  // Update the piece's has_moved
  move.piece->setHasMoved(true);

  // Update the piece's legal moves
  this->updateMovesForAllPieces();

  // Add the move to the stack
  this->addMoveToStack(move);

  this->setEnPassantSquare();
}

void Board::updateMovesForAllPieces() {
  for (Piece* piece : board) {
    if (piece != nullptr) {
      piece->updateLegalMoves(board);
    }
  }
}

void Board::setEnPassantSquare() {
  // Get the last move
  Move last_move = move_stack.top();

  // If the last move was not a pawn, return
  if (!last_move.piece->isPawn()) {
    return;
  }

  // If the last move was not two squares, return
  if (abs(last_move.from_square - last_move.to_square) != 16) {
    return;
  }

  int directions[2] = {-1, 1};

  for (int i = 0; i < 2; i++) {
    int square = last_move.to_square + directions[i];

    // If the square is not on the board, continue
    if (square < 0 || square > 63) {
      continue;
    }

    // If the square to the side of the pawn is empty, no en passant
    if (board[square] == nullptr) {
      continue;
    }

    // The other piece must be a different color
    if (board[square]->getColor() == last_move.piece->getColor()) {
      continue;
    }

    // If the square to the side of the pawn is not a pawn, no en passant
    if (!board[square]->isPawn()) {
      continue;
    }

    Pawn* pawn = static_cast<Pawn*>(board[square]);
    int color_offset = pawn->getColor() == WHITE ? -8 : 8;

    pawn->addEnPassantSquare(last_move.to_square + color_offset);
  }
}