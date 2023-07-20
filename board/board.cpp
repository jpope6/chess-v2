#include "board.h"

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
        Piece* piece = createPiece(c, row, col);

        board[row][col] = piece;
        col++;
      }
    }
  }
}

Piece* Board::createPiece(char c, int row, int col) {
  switch (c) {
    case 'P':
    case 'p':
      return new Pawn(row, col, c);
    case 'R':
    case 'r':
      return new Rook(row, col, c);
    case 'B':
    case 'b':
      return new Bishop(row, col, c);
    case 'N':
    case 'n':
      return new Knight(row, col, c);
    case 'Q':
    case 'q':
      return new Queen(row, col, c);
    case 'K':
    case 'k':
      return new King(row, col, c);
    default:
      return nullptr;  // Invalid piece character
  }
}

// Move a piece on the board
// Return true if the move was successful, false otherwise
bool Board::movePiece(int from_row, int from_col, int to_row, int to_col) {
  // If moving to the same square, return false
  if (from_row == to_row && from_col == to_col) {
    return false;
  }

  Piece* piece = board[from_row][from_col];

  // If there is no piece at the from square, return false
  if (piece == nullptr) {
    return false;
  }

  if (piece->isLegalMove(to_row, to_col)) {
    piece->setRow(to_row);
    piece->setCol(to_col);

    piece->setHasMoved(true);

    // If the pawn does an en passant capture
    if (piece->isPawn() && from_col != to_col &&
        board[to_row][to_col] == nullptr) {
      removeEnPassantPiece();
    }

    // Handle capture and moves
    handleMove(from_row, from_col, to_row, to_col);

    // Add the move to the stack
    addMoveToStack(from_row, from_col, to_row, to_col, piece);

    // If there is no en passant square, reset it
    if (!setEnPassantSquare()) {
      en_passant_row = -1;
      en_passant_col = -1;
    }

    // Move is legal, return true
    return true;
  }

  // Move is illegal, return false
  return false;
}

// Handle capture and moves
void Board::handleMove(int from_row, int from_col, int to_row, int to_col) {
  Piece* piece = board[from_row][from_col];

  // If there is no piece at the from square, return false
  if (piece == nullptr) {
    return;
  }

  // If the move is a capture
  if (board[to_row][to_col] != nullptr) {
    delete board[to_row][to_col];
  }

  // Move the piece
  board[to_row][to_col] = piece;
  board[from_row][from_col] = nullptr;
}

// Add the last move onto the stack
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

// If the last move was a pawn moving two squares, set the en passant square
bool Board::setEnPassantSquare() {
  // Get the last move
  ChessMove move = getLastMove();

  // If the last move was a pawn moving two squares
  if (move.piece->isPawn()) {
    if (abs(move.from_row - move.to_row) == 2) {
      int color_offset = move.piece->colorOffset();

      en_passant_row = move.to_row - (1 * color_offset);
      en_passant_col = move.to_col;

      return true;
    }
  }

  return false;
}

// If the last move was an en passant capture, remove the captured piece
void Board::removeEnPassantPiece() {
  // check if the last move was an en passant capture
  ChessMove move = getLastMove();
  delete board[move.to_row][move.to_col];
  board[move.to_row][move.to_col] = nullptr;
}
