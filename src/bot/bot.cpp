#include "bot.h"

Bot::Bot(){};

pair<int, int> Bot::makeMove(vector<Piece *> pieces) {
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
