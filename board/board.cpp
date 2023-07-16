#include "board.h"

Board::Board() {
  // Starting FEN string
  fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  board = vector<vector<Piece*>>(8, vector<Piece*>(8, nullptr));
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
    if (c == '/') {  // If we reach the end of a row
      row++;
      col = 0;
    } else {
      if (isdigit(c)) {  // If the character is a number
        int num = c - '0';

        // Fill the empty squares with spaces
        while (col < num) {
          board[row][col] = nullptr;
          col++;
        }
      } else {
        Piece* piece = nullptr;

        // Create a piece based on the character
        switch (c) {
          case 'P':
          case 'p':
            piece = new Pawn(row, col, c);
            break;

          case 'R':
          case 'r':
            piece = new Rook(row, col, c);
            break;

          case 'B':
          case 'b':
            piece = new Bishop(row, col, c);
            break;

          case 'N':
          case 'n':
            piece = new Knight(row, col, c);
            break;

          case 'Q':
          case 'q':
            piece = new Queen(row, col, c);
            break;

          case 'K':
          case 'k':
            piece = new King(row, col, c);
            break;

          default:
            break;
        }

        board[row][col] = piece;
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

  // Check if the move is in the pieces legal moves
  vector<Move> legal_moves = board[from_row][from_col]->updateLegalMoves(board);

  // If the move is not legal, return false
  for (Move move : legal_moves) {
    if (move.row == to_row && move.col == to_col) {
      // Store the new row and column
      board[from_row][from_col]->setRow(to_row);
      board[from_row][from_col]->setCol(to_col);

      board[from_row][from_col]->setHasMoved(true);

      // Move the piece
      board[to_row][to_col] = board[from_row][from_col];
      board[from_row][from_col] = nullptr;

      return true;
    }
  }

  return false;
}