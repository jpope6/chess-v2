#include "board.h"

#include <iostream>

Board::Board() {
  fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

  // Set the starting board
  setBoardWithFenString(fen_string);

  // Set the kings
  white_king = board[4];
  black_king = board[60];
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
        board[row * 8 + col] = createPiece(c, row, col);
        col++;
      }
    }
  }
}

// Create a piece based on the character
Piece* Board::createPiece(char c, int row, int col) {
  int square = row * 8 + col;

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
