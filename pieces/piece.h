#ifndef PIECE_H
#define PIECE_H

#include <cctype>
#include <map>

using namespace std;

enum Color { WHITE = 0, BLACK = 1 };

enum Type { PAWN = 0, KNIGHT = 1, BISHOP = 2, ROOK = 3, QUEEN = 4, KING = 5 };

enum Column { A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7 };

class Piece {
 private:
  int row;
  int col;
  int square;
  char name;
  Color color;
  Type piece_type;
  bool has_moved;

 public:
  // Constructor
  Piece(int square, char piece);

  // Getters
  char getName() { return name; }
};

#endif