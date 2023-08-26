#include "bot.h"

Bot::Bot() {
  // Map a point value to the piece type
  this->eval_map = {
      {'P', 10},  {'N', 30},  {'B', 30},  {'R', 50},  {'Q', 90},  {'K', 900},
      {'p', -10}, {'n', -30}, {'b', -30}, {'r', -50}, {'q', -90}, {'k', -900},
  };

  this->color = BLACK;
}

pair<int, int> Bot::makeMove(Piece *board[64], vector<Piece *> pieces) {
  pair<int, int> best_move;
  int best_score = -9999;

  vector<pair<int, int>> legal_moves = this->getAllLegalMoves(pieces);

  for (auto &move : legal_moves) {
    // Play the move
    Piece *original_piece = board[move.second];

    // Temporarily move the piece
    board[move.second] = board[move.first];
    board[move.first] = nullptr;
    board[move.second]->setSquare(move.second);

    // evaluate board
    int score = this->evaluateBoard(board) * this->getColorOffset();
    if (score > best_score) {
      best_score = score;
      best_move = move;
    }

    // Move the piece back
    board[move.first] = board[move.second];
    board[move.second] = original_piece;
    board[move.first]->setSquare(move.first);
  }

  return best_move;
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

// Get the value of the input piece
int Bot::getPieceValue(Piece *piece) {
  return this->eval_map[piece->getName()];
}

// Evaluate the entire board
int Bot::evaluateBoard(Piece *board[64]) {
  int sum = 0;

  for (int i = 0; i < 64; i++) {
    if (board[i] != nullptr) {
      sum = sum + this->getPieceValue(board[i]);
    }
  }

  return sum;
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

int Bot::getColorOffset() { return this->color == WHITE ? 1 : -1; }
