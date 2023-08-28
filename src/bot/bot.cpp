#include "bot.h"
#include <climits>
#include <utility>

Bot::Bot() {
  this->board = Board();
  this->setChessboard();
  this->color = BLACK;
  this->king = this->color == WHITE ? this->board.getWhiteKing()
                                    : this->board.getBlackKing();
  this->depth = 3;
  this->positions_evaluated = 0;

  // Map a point value to the piece type
  this->eval_map = {
      {'P', 100},  {'N', 320},   {'B', 330},  {'R', 500},
      {'Q', 900},  {'K', 20000}, {'p', -100}, {'n', -320},
      {'b', -330}, {'r', -500},  {'q', -900}, {'k', -20000},
  };
}

pair<int, int> Bot::makeMove() {
  this->best_move = make_pair(8, 24);

  int eval = this->search(this->depth, INT_MIN, INT_MAX);

  return this->best_move;
}

int Bot::search(int depth, int alpha, int beta) {
  if (depth == 0) {
    return this->evaluateBoard();
  }

  vector<pair<int, int>> legal_moves =
      this->getAllLegalMoves(this->getPieces());

  if (legal_moves.empty()) {
    if (this->king->getIsInCheck()) {
      return INT_MIN;
    }
    return 0;
  }

  for (auto &move : legal_moves) {
    // Play the move
    Piece *original_piece = this->chessboard[move.second];

    // Temporarily move the piece
    this->chessboard[move.second] = this->chessboard[move.first];
    this->chessboard[move.first] = nullptr;
    this->chessboard[move.second]->setSquare(move.second);
    this->chessboard[move.second]->updateLegalMoves(this->chessboard);

    int eval = -this->search(depth - 1, -beta, -alpha);

    // Move the piece back
    this->chessboard[move.first] = this->chessboard[move.second];
    this->chessboard[move.second] = original_piece;
    this->chessboard[move.first]->setSquare(move.first);
    this->chessboard[move.first]->updateLegalMoves(this->chessboard);

    if (eval >= beta) {
      return beta;
    }

    if (eval > alpha) {
      this->best_move = move;

      alpha = eval;
    }
  }
  return alpha;
}

pair<int, int> Bot::makeRandomMove(vector<Piece *> pieces) {
  int size = 0;
  int random_index = 0;
  Piece *random_piece = nullptr;

  srand(static_cast<unsigned int>(time(nullptr)));

  while (size == 0) {
    random_index = rand() % pieces.size();
    random_piece = pieces[random_index];
    size = random_piece->getLegalMoves().size();
  }

  random_index = rand() % random_piece->getLegalMoves().size();

  pair<int, int> move = make_pair(random_piece->getSquare(),
                                  random_piece->getLegalMoves()[random_index]);

  return move;
}

void Bot::sortMoves(vector<pair<int, int>> &moves) {
  for (auto &move : moves) {
    int score = 0;
    Piece *move_piece = this->chessboard[move.first];
    Piece *captured_piece = this->chessboard[move.second];

    this->board.handleMove(move.first, move.second);

    if (captured_piece != nullptr) {
      score = 10 * this->getPieceValue(captured_piece) -
              this->getPieceValue(move_piece);
    }

    // Pick which type of promotion here
    if (this->board.isPawnPromoting()) {
      score += 900;
    }

    this->board.undoLastMove();
  }
}

// Get the value of the input piece
int Bot::getPieceValue(Piece *piece) {
  return this->eval_map[piece->getName()];
}

// Evaluate the entire board
int Bot::evaluateBoard() {
  int white_eval = 0;
  int black_eval = 0;
  int eval = 0;

  for (int i = 0; i < 64; i++) {
    if (this->chessboard[i] == nullptr) {
      continue;
    }

    if (this->chessboard[i]->getColor() == WHITE) {
      white_eval += this->getPieceValue(this->chessboard[i]);
    } else {
      black_eval += this->getPieceValue(this->chessboard[i]);
    }
  }

  eval = white_eval - black_eval;
  return eval * this->getColorOffset();
}

vector<Piece *> Bot::getPieces() {
  vector<Piece *> pieces = {};

  for (int i = 0; i < 64; i++) {
    if (this->chessboard[i] != nullptr &&
        this->chessboard[i]->getColor() == this->color) {
      pieces.push_back(this->chessboard[i]);
    }
  }

  return pieces;
}

// Return a pair of <home square, target square> for all legal moves
vector<pair<int, int>> Bot::getAllLegalMoves(vector<Piece *> pieces) {
  vector<pair<int, int>> legal_moves = {};

  for (Piece *piece : pieces) {
    if (piece->getColor() != this->color) {
      continue;
    }

    for (int legal_move : piece->getLegalMoves()) {
      pair<int, int> move = make_pair(piece->getSquare(), legal_move);
      legal_moves.push_back(move);
    }
  }

  return legal_moves;
}

// End game conditions:
// 1. Both sides have no queens or
// 2. Every side which has a queen has additionally no other pieces or one
//      minorpiece maximum.
bool Bot::isEndgame() {
  bool white_queen = false;
  bool black_queen = false;
  int white_minor_pieces = 0;
  int black_minor_pieces = 0;

  for (int i = 0; i < 64; i++) {
    if (this->board.getBoard()[i] == nullptr) {
      continue;
    }

    switch (this->board.getBoard()[i]->getName()) {
    case 'Q':
      white_queen = true;
      if (white_minor_pieces > 1) {
        return false;
      }
      break;
    case 'q':
      black_queen = true;
      if (black_minor_pieces > 1) {
        return false;
      }
      break;
    case 'B':
    case 'N':
      white_minor_pieces++;
      if (black_queen) {
        return false;
      }
      break;
    case 'b':
    case 'n':
      black_minor_pieces++;
      if (white_queen) {
        return false;
      }
      break;
    default:
      break;
    }
  }

  return (!white_queen || white_minor_pieces <= 1) &&
         (!black_queen || black_minor_pieces <= 1);
}

int Bot::getColorOffset() { return this->color == WHITE ? 1 : -1; }

int *Bot::getPieceTable(Piece *piece, Piece *board[64]) {
  switch (piece->getName()) {
  case 'P':
    return this->pawn_table;
  case 'p':
    return this->reverseTable(this->pawn_table);
  case 'R':
    return this->rook_table;
  case 'r':
    return this->reverseTable(this->rook_table);
  case 'B':
    return this->bishop_table;
  case 'b':
    return this->reverseTable(this->bishop_table);
  case 'N':
    return this->knight_table;
  case 'n':
    return this->reverseTable(this->knight_table);
  case 'Q':
    return this->queen_table;
  case 'q':
    return this->reverseTable(this->queen_table);
  case 'K':
    if (this->isEndgame()) {
      return this->king_endgame_table;
    } else {
      return this->king_midgame_table;
    }
  case 'k':
    if (this->isEndgame()) {
      return this->reverseTable(this->king_endgame_table);
    } else {
      return this->reverseTable(this->king_midgame_table);
    }
  default:
    return nullptr;
  }
}

int *Bot::reverseTable(int table[64]) {
  int *reversed_table = new int[64];

  for (int i = 0; i < 64; i++) {
    reversed_table[i] = 0;
  }

  int start = 0;
  int end = 63;

  while (start < end) {
    reversed_table[start] = table[end];
    reversed_table[end] = table[start];

    start++;
    end--;
  }

  return reversed_table;
}
