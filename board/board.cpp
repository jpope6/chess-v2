#include "board.h"

Board::Board() {
  // Starting FEN string
  fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
}

Board::~Board() {}

// Set the board with the FEN string
void Board::setBoardWithFenString(string fen_string) {
  // Get the board part of the FEN string
  string fen_board = fen_string.substr(0, fen_string.find(" "));

  int row = 0;
  int col = 0;

  // Loop through the FEN board string
  for (char c : fen_board) {

    if (c == '/') { // If we reach the end of a row
      row++;
      col = 0;
    } else {
      if (isdigit(c)) { // If the character is a number
        int num = c - '0';

        // Fill the empty squares with spaces
        while (col < num) {
          board[row][col] = ' ';
          col++;
        }
      } else {
        // Fill the squares with the piece
        board[row][col] = c;
        col++;
      }
    }
  }
}

// Move a piece on the board
// Return true if the move was successful, false otherwise
bool Board::movePiece(int from_row, int from_col, int to_row, int to_col) {
  // If moving to the same square, return false
  if (from_row == to_row && from_col == to_col) {
    return false;
  }

  // Move the piece
  board[to_row][to_col] = board[from_row][from_col];
  board[from_row][from_col] = ' ';

  return true;
}