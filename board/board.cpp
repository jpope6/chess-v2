#include "board.h"

#include <iostream>

Board::Board() {
  // Starting FEN string
  fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  board = vector<vector<Piece*>>(8, vector<Piece*>(8, nullptr));
  move_stack = stack<ChessMove>();

  en_passant_row = -1;
  en_passant_col = -1;
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

        // Fill the empty squares with nullptr
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

// Update legal moves for all pieces
void Board::updateLegalMoves() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      // If there is a piece at the current square
      if (board[row][col] != nullptr) {
        // Update the legal moves for the piece
        board[row][col]->updateLegalMoves(board);
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
  vector<Move> legal_moves = board[from_row][from_col]->getPotentialMoves();

  for (Move move : legal_moves) {
    if (move.row == to_row && move.col == to_col) {
      Piece* piece = board[from_row][from_col];

      // Store the new row and column
      piece->setRow(to_row);
      piece->setCol(to_col);

      piece->setHasMoved(true);

      // Move the piece
      board[to_row][to_col] = piece;
      board[from_row][from_col] = nullptr;

      // Add the move to the stack
      addMoveToStack(from_row, from_col, to_row, to_col, piece);

      if (!setEnPassantSquare()) {
        en_passant_row = -1;
        en_passant_col = -1;
      }

      // Move is legal, return true
      return true;
    }
  }

  // Move is illegal, return false
  return false;
}

void Board::addMoveToStack(int from_row, int from_col, int to_row, int to_col,
                           Piece* piece) {
  ChessMove move;
  move.from_row = from_row;
  move.from_col = from_col;
  move.to_row = to_row;
  move.to_col = to_col;
  move.piece = piece;

  move_stack.push(move);
}

bool Board::setEnPassantSquare() {
  // Get the last move
  ChessMove move = getLastMove();

  // If the last move was a pawn moving two squares
  if (move.piece->isPawn()) {
    if (abs(move.from_row - move.to_row) == 2) {
      int color_offset = move.piece->colorOffset();

      en_passant_row = move.to_row + (1 * color_offset);
      en_passant_col = move.to_col;

      cout << "En passant square: " << en_passant_row << ", " << en_passant_col
           << endl;

      return true;
    }
  }

  return false;
}