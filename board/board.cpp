#include "board.h"

#include <iostream>

Board::Board() {
  // Starting FEN string
  fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  board = vector<vector<Piece*>>(8, vector<Piece*>(8, nullptr));
  move_stack = stack<ChessMove>();

  en_passant_row = -1;
  en_passant_col = -1;

  white_king = nullptr;
  black_king = nullptr;
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

// Create a piece based on the character
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
      white_king = new King(row, col, c);
      return white_king;
    case 'k':
      black_king = new King(row, col, c);
      return black_king;
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

    // If the king castled, move the rook
    if (piece->isKing()) {
      moveRookOnCastle();
    }

    updateWhiteMoves();
    updateBlackMoves();

    if (isWhiteKingInCheck()) {
      cout << "White king is in check" << endl;
    }

    if (isBlackKingInCheck()) {
      cout << "Black king is in check" << endl;
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

void Board::updateWhiteMoves() {
  white_moves = {};

  for (const auto& row : board) {
    for (const auto& piece : row) {
      if (piece != nullptr && piece->getIsWhite()) {
        vector<Move> legal_moves = piece->updateLegalMoves(board);

        for (const auto& move : legal_moves) {
          white_moves.push_back(move);
        }
      }
    }
  }
}

void Board::updateBlackMoves() {
  black_moves = {};

  for (const auto& row : board) {
    for (const auto& piece : row) {
      if (piece != nullptr && piece->getIsBlack()) {
        vector<Move> legal_moves = piece->updateLegalMoves(board);

        for (const auto& move : legal_moves) {
          black_moves.push_back(move);
        }
      }
    }
  }
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

bool Board::canCastle(Piece* king, int row, int king_col, int rook_col) {
  // if the king is not on the board yet
  if (king == nullptr) {
    return false;
  }

  // if the king has moved
  if (king->getHasMoved()) {
    return false;
  }

  // Direction of castling
  int direction = rook_col > king_col ? 1 : -1;
  int start = king_col + direction;
  int end = rook_col;

  // if there is a piece in the way of the king
  for (int col = start; col != end; col += direction) {
    if (board[row][col] != nullptr) {
      return false;
    }
  }

  // if the rook was captured
  if (board[row][rook_col] == nullptr) {
    return false;
  }

  // if the rook has moved
  if (board[row][rook_col]->getHasMoved()) {
    return false;
  }

  // TODO: if the king is in check

  // TODO: if the king moves through check

  return true;
}

// Check if white can castle king side
bool Board::whiteCanCastleKingSide() { return canCastle(white_king, 7, 4, 7); }

bool Board::whiteCanCastleQueenSide() { return canCastle(white_king, 7, 4, 0); }

bool Board::blackCanCastleKingSide() { return canCastle(black_king, 0, 4, 7); }

bool Board::blackCanCastleQueenSide() { return canCastle(black_king, 0, 4, 0); }

// Move the rook on castling
void Board::moveRookOnCastle() {
  ChessMove move = getLastMove();

  // If the king moved to the right two squares
  if (move.to_col - move.from_col == 2) {
    // Move the rook to the left of the king
    board[move.to_row][move.to_col - 1] = board[move.to_row][move.to_col + 1];

    // Update the rooks column
    Piece* rook = board[move.to_row][move.to_col - 1];
    rook->setCol(move.to_col - 1);

    board[move.to_row][move.to_col + 1] = nullptr;
  } else if (move.to_col - move.from_col == -2) {
    // Move the rook to the right of the king
    board[move.to_row][move.to_col + 1] = board[move.to_row][move.to_col - 2];

    // Update the rooks column
    Piece* rook = board[move.to_row][move.to_col + 1];
    rook->setCol(move.to_col + 1);

    board[move.to_row][move.to_col - 2] = nullptr;
  }
}

// Check if the king is in check
bool Board::isKingInCheck(Piece* king, vector<Move>& moves) {
  if (king == nullptr) {
    return false;
  }

  for (const auto& move : moves) {
    if (move.row == king->getRow() && move.col == king->getCol()) {
      return true;
    }
  }

  return false;
}

bool Board::isWhiteKingInCheck() {
  return isKingInCheck(white_king, black_moves);
}

bool Board::isBlackKingInCheck() {
  return isKingInCheck(black_king, white_moves);
}

// Get the path of the piece checking the king
vector<Move> Board::getCheckPath(Piece* king, vector<Move>& moves) {
  vector<Move> path = {};

  if (king == nullptr) {
    return path;
  }

  for (const auto& row : board) {
    for (Piece* piece : row) {
      if (piece != nullptr && !piece->isSameColor(king)) {
        vector<Move> legal_moves = piece->updateLegalMoves(board);

        for (const auto& move : legal_moves) {
          for (const auto& path_move : moves) {
            if (move.row == path_move.row && move.col == path_move.col) {
              path.push_back(move);
            }
          }
        }
      }
    }
  }

  return path;
}

void Board::updateMovesInCheck(Piece* king, Piece* selected_piece) {
  updateBlackMoves();

  if (!isKingInCheck(king, black_moves)) {
    return;
  }

  vector<Move> check_path = getCheckPath(king, black_moves);

  for (const auto& row : board) {
    for (Piece* piece : row) {
      vector<Move> legal_moves = {};
      if (piece != nullptr && piece->isSameColor(king)) {
        for (const auto& move : piece->updateLegalMoves(board)) {
          for (const auto& path_move : check_path) {
            if (move.row == path_move.row && move.col == path_move.col) {
              legal_moves.push_back(move);
            }
          }
        }

        piece->setPotentialMoves(legal_moves);
      }
    }
  }
}