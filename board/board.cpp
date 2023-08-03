#include "board.h"

#include <iostream>

Board::Board() {
  fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

  turn = WHITE;

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
    if (c == '/') { // If we reach the end of a row
      row++;
      col = 0;
    } else {
      if (isdigit(c)) { // If the character is a number
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
Piece *Board::createPiece(int square, char c) {
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
    return nullptr; // Invalid piece character
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
    move.captured_piece = board[to_square];
    delete board[to_square];
  } else {
    move.captured_piece = nullptr;
  }

  board[to_square] = move.piece;
  board[from_square] = nullptr;

  // Update the piece's square
  move.piece->setSquare(to_square);

  // Update the piece's has_moved
  move.piece->setHasMoved(true);

  // Add the move to the stack
  this->addMoveToStack(move);

  this->handleEnPassantCapture();
  this->moveRookOnCastle();

  this->changeTurn();
}

void Board::updateMovesForAllPieces() {
  for (Piece *piece : board) {
    if (piece != nullptr) {
      piece->updateLegalMoves(board);
    }
  }
}

void Board::changeTurn() {
  if (turn == WHITE) {
    turn = BLACK;
  } else {
    turn = WHITE;
  }

  this->updateMovesForAllPieces();
  this->setEnPassantSquare();
  this->handleKingCheck();
  this->handleCastlingRights();
  this->updateMovesForPinnedPieces();
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

    Pawn *pawn = static_cast<Pawn *>(board[square]);
    int color_offset = pawn->getColor() == WHITE ? -8 : 8;

    pawn->addEnPassantSquare(last_move.to_square + color_offset);
  }
}

void Board::handleEnPassantCapture() {
  // Get the last move
  Move last_move = move_stack.top();

  // If the last move was not a pawn, return
  if (!last_move.piece->isPawn()) {
    return;
  }

  // If last move was not a diagonal move, return
  if (abs(last_move.from_square - last_move.to_square) != 9 &&
      abs(last_move.from_square - last_move.to_square) != 7) {
    return;
  }

  // If the diagonal square is nullptr, delete the en passant captured pawn
  if (last_move.captured_piece == nullptr) {
    int color_offset = last_move.piece->getColor() == WHITE ? 8 : -8;
    last_move.captured_piece = board[last_move.to_square + color_offset];
    delete board[last_move.to_square + color_offset];
    board[last_move.to_square + color_offset] = nullptr;
  }
}

void Board::handleCastlingRights() {
  King *king = turn == WHITE ? white_king : black_king;

  if (king->getHasMoved()) {
    return;
  }

  // Get the rook square
  int king_side_rook_square = king->getSquare() + 3;
  king->setCastlingSquare(this->board, king_side_rook_square,
                          pieces_attacking_king);

  int queen_side_rook_square = king->getSquare() - 4;
  king->setCastlingSquare(this->board, queen_side_rook_square,
                          pieces_attacking_king);
}

void Board::moveRookOnCastle() {
  // Get the last move
  Move last_move = move_stack.top();

  // If the last move was not a king, return
  if (!last_move.piece->isKing()) {
    return;
  }

  // If the last move was not a castle, return
  if (abs(last_move.from_square - last_move.to_square) != 2) {
    return;
  }

  // Get the rook square
  int rook_square = last_move.to_square > last_move.from_square
                        ? last_move.to_square + 1
                        : last_move.to_square - 2;
  // The square the rook will move to
  int target_square = last_move.to_square > last_move.from_square
                          ? last_move.to_square - 1
                          : last_move.to_square + 1;

  // Move the rook
  board[target_square] = board[rook_square];
  board[rook_square] = nullptr;

  // Update the rook's square
  board[target_square]->setSquare(target_square);
  board[target_square]->setHasMoved(true);
}

void Board::handleKingCheck() {
  King *king = turn == WHITE ? white_king : black_king;

  // Get all the pieces of the opposite color
  std::vector<Piece *> pieces;

  for (Piece *piece : board) {
    if (piece != nullptr && piece->getColor() != turn) {
      pieces.push_back(piece);
    }
  }

  if (king->isInCheck(board, pieces, pieces_attacking_king)) {
    cout << "King is in check" << endl;
    // this->updateMovesInCheck();
  }
}

void Board::updateMovesInCheck() {
  King *king = turn == WHITE ? white_king : black_king;
  vector<int> moves_that_stop_check = {};

  // Moves that stop check are moves that block the path to the king
  for (Piece *piece : pieces_attacking_king) {
    for (const int square : piece->getPathToKing(board, king)) {
      moves_that_stop_check.push_back(square);
    }
  }

  // Update legal moves that that they can only move to squares that stop check
  for (Piece *piece : board) {
    vector<int> new_legal_moves;
    if (piece != nullptr && piece->getColor() == turn && !piece->isKing()) {
      for (int move : piece->getLegalMoves()) {
        // If there is a move in the pieces legal moves that stops check
        // Add it to the new legal moves
        if (find(moves_that_stop_check.begin(), moves_that_stop_check.end(),
                 move) != moves_that_stop_check.end()) {
          new_legal_moves.push_back(move);
        }

        // If the move can capture the piece attacking the king
        for (Piece *attacking_piece : pieces_attacking_king) {
          if (attacking_piece->getSquare() == move) {
            new_legal_moves.push_back(move);
          }
        }
      }

      // Set the new legal moves for the piece
      piece->setLegalMoves(new_legal_moves);
    }
  }
}

// This works for now but I do not like it
// TODO: MAKE THIS BETTER
void Board::updateMovesForPinnedPieces() {
  King *king = turn == WHITE ? white_king : black_king;

  vector<Piece *> not_turn_pieces = {};
  vector<Piece *> turn_pieces = {};

  for (Piece *piece : board) {
    if (piece != nullptr) {
      if (piece->getColor() == turn) {
        turn_pieces.push_back(piece);
      } else {
        not_turn_pieces.push_back(piece);
      }
    }
  }

  for (Piece *piece : turn_pieces) {
    if (piece->isKing()) {
      continue;
    }

    pieces_attacking_king = {};

    for (int move : piece->getLegalMoves()) {
      int original_square = piece->getSquare();
      Piece *original_piece = board[move];

      // Temporarily move the piece
      board[move] = piece;
      board[original_square] = nullptr;
      piece->setSquare(move);

      // Update moves for opposite turn pieces
      for (Piece *piece : not_turn_pieces) {
        piece->updateLegalMoves(board);
      }

      // If the king is in check, remove the move
      if (king->isInCheck(board, not_turn_pieces, pieces_attacking_king)) {
        piece->removeLegalMove(move);
      }

      for (Piece *attacking_piece : pieces_attacking_king) {
        for (int square : attacking_piece->getPathToKing(board, king)) {
          if (square == move || move == attacking_piece->getSquare()) {
            piece->addLegalMove(move);
          }
        }

        // If the move can capture the piece attacking the king
        if (attacking_piece->getSquare() == move) {
          piece->addLegalMove(move);
        }
      }

      // Move the piece back
      board[move] = original_piece;
      board[original_square] = piece;
      piece->setSquare(original_square);
    }
  }
}
