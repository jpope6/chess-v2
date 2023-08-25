#ifndef BOT_H
#define BOT_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

#include "../pieces/piece.h"

using namespace std;

class Bot {
private:
public:
  // Constructor
  Bot();

  // Member functions
  pair<int, int> makeMove(vector<Piece *> pieces);
};

#endif
