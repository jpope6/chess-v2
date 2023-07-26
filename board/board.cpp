#include "board.h"

#include <iostream>

Board::Board() {
  fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

  cout << "Board constructor" << endl;

  // Set the starting board
  setBoardWithFenString(fen_string);

  printBoard();
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
  board[to_square] = move.piece;
  board[from_square] = nullptr;

  // Update the piece's square
  move.piece->setSquare(to_square);

  // Update the piece's has_moved
  move.piece->setHasMoved(true);

  // Update the piece's legal moves
  // this->updateMovesForAllPieces();

  // Add the move to the stack
  this->addMoveToStack(move);
}

void Board::updateMovesForAllPieces() {
  for (Piece* piece : board) {
    if (piece != nullptr) {
      piece->updateLegalMoves(board);
    }
  }
}

void Board::printBoard() {
  for (int i = 0; i < 64; i++) {
    if (board[i] == nullptr) {
      cout << "0 ";
    } else {
      cout << board[i]->getName() << " ";
    }
    if (i % 8 == 7) {
      cout << endl;
    }
  }
}