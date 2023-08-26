#ifndef BOT_H
#define BOT_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "../pieces/piece.h"

using namespace std;

class Bot {
private:
  map<char, int> eval_map;

  Color color;

public:
  // Constructor
  Bot();

  // Member functions
  pair<int, int> makeMove(Piece *board[64], vector<Piece *> pieces);
  pair<int, int> makeRandomMove(vector<Piece *> pieces);
  int getPieceValue(Piece *piece);
  int evaluateBoard(Piece *board[64]);
  vector<pair<int, int>> getAllLegalMoves(vector<Piece *> pieces);
  int getColorOffset();
};

#endif
