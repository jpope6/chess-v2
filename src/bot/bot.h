#ifndef BOT_H
#define BOT_H

#include "limits.h"
#include <iostream>

#include "../board/board.h"

using namespace std;

class Bot {
private:
  Board board;
  Piece *chessboard[64];

  pair<int, int> best_move;

  int depth;
  map<char, int> eval_map;
  Color color;
  int positions_evaluated;

  King *king;

  int pawn_table[64] = {0,   0,  0,  0,   0,  0,  0,   0,  50, 50, 50, 50, 50,
                        50,  50, 50, 10,  10, 20, 30,  30, 20, 10, 10, 5,  5,
                        10,  25, 25, 10,  5,  5,  0,   0,  0,  20, 20, 0,  0,
                        0,   5,  -5, -10, 0,  0,  -10, -5, 5,  5,  10, 10, -20,
                        -20, 10, 10, 5,   0,  0,  0,   0,  0,  0,  0,  0};

  int knight_table[64] = {-50, -40, -30, -30, -30, -30, -40, -50, -40, -20, 0,
                          0,   0,   0,   -20, -40, -30, 0,   10,  15,  15,  10,
                          0,   -30, -30, 5,   15,  20,  20,  15,  5,   -30, -30,
                          0,   15,  20,  20,  15,  0,   -30, -30, 5,   10,  15,
                          15,  10,  5,   -30, -40, -20, 0,   5,   5,   0,   -20,
                          -40, -50, -40, -30, -30, -30, -30, -40, -50};

  int bishop_table[64] = {-20, -10, -10, -10, -10, -10, -10, -20, -10, 0,   0,
                          0,   0,   0,   0,   -10, -10, 0,   5,   10,  10,  5,
                          0,   -10, -10, 5,   5,   10,  10,  5,   5,   -10, -10,
                          0,   10,  10,  10,  10,  0,   -10, -10, 10,  10,  10,
                          10,  10,  10,  -10, -10, 5,   0,   0,   0,   0,   5,
                          -10, -20, -10, -10, -10, -10, -10, -10, -20};

  int rook_table[64] = {0,  0,  0, 0,  0, 0,  0,  0, 5,  10, 10, 10, 10,
                        10, 10, 5, -5, 0, 0,  0,  0, 0,  0,  -5, -5, 0,
                        0,  0,  0, 0,  0, -5, -5, 0, 0,  0,  0,  0,  0,
                        -5, -5, 0, 0,  0, 0,  0,  0, -5, -5, 0,  0,  0,
                        0,  0,  0, -5, 0, 0,  0,  5, 5,  0,  0,  0};

  int queen_table[64] = {-20, -10, -10, -5,  -5,  -10, -10, -20, -10, 0,  0,
                         0,   0,   0,   0,   -10, -10, 0,   5,   5,   5,  5,
                         0,   -10, -5,  0,   5,   5,   5,   5,   0,   -5, 0,
                         0,   5,   5,   5,   5,   0,   -5,  -10, 5,   5,  5,
                         5,   5,   0,   -10, -10, 0,   5,   0,   0,   0,  0,
                         -10, -20, -10, -10, -5,  -5,  -10, -10, -20};

  int king_midgame_table[64] = {
      -30, -40, -40, -50, -50, -40, -40, -30, -30, -40, -40, -50, -50,
      -40, -40, -30, -30, -40, -40, -50, -50, -40, -40, -30, -30, -40,
      -40, -50, -50, -40, -40, -30, -20, -30, -30, -40, -40, -30, -30,
      -20, -10, -20, -20, -20, -20, -20, -20, -10, 20,  20,  0,   0,
      0,   0,   20,  20,  20,  30,  10,  0,   0,   10,  30,  20};

  int king_endgame_table[64] = {
      -50, -40, -30, -20, -20, -30, -40, -50, -30, -20, -10, 0,   0,
      -10, -20, -30, -30, -10, 20,  30,  30,  20,  -10, -30, -30, -10,
      30,  40,  40,  30,  -10, -30, -30, -10, 30,  40,  40,  30,  -10,
      -30, -30, -10, 20,  30,  30,  20,  -10, -30, -30, -30, 0,   0,
      0,   0,   -30, -30, -50, -30, -30, -30, -30, -30, -30, -50};

public:
  // Constructor
  Bot();

  // Getters
  Board &getBoard() { return this->board; }
  Piece **getChessboard() { return this->board.getBoard(); }
  Color getColor() { return this->color; }

  // Setters
  void setChessboard() {
    for (int i = 0; i < 64; i++) {
      this->chessboard[i] = this->getChessboard()[i];
    }
  }

  // Member functions
  pair<int, int> makeMove();
  pair<int, int> makeRandomMove(vector<Piece *> pieces);
  int search(int depth, int alpha, int beta);
  void sortMoves(vector<pair<int, int>> &moves);
  int getPieceValue(Piece *piece);
  int evaluateBoard();
  vector<Piece *> getPieces();
  vector<pair<int, int>> getAllLegalMoves(vector<Piece *> pieces);
  int getColorOffset();
  bool isEndgame();
  int *getPieceTable(Piece *piece, Piece *board[64]);
  int *reverseTable(int table[64]);
};

#endif
