#ifndef PIECE_H
#define PIECE_H

#include <cctype>
#include <cmath>
#include <map>
#include <vector>

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

  vector<int> legal_moves;

 public:
  // Constructor
  Piece(int square, char piece);

  // Destructor
  virtual ~Piece() = default;

  // Getters
  char getName() { return name; }
  int getRow() { return row; }
  int getCol() { return col; }
  int getSquare() { return square; }
  Color getColor() { return color; }
  vector<int> getLegalMoves() { return legal_moves; }

  // Setters
  void setSquare(int square) {
    this->row = square / 8;
    this->col = square % 8;
    this->square = square;
  }
  void setLegalMoves(vector<int> legal_moves) {
    this->legal_moves = legal_moves;
  }
  void setHasMoved(bool has_moved) { this->has_moved = has_moved; }

  // Virtual functions
  virtual void updateLegalMoves(Piece* board[64]) = 0;

  // Member functions
  void getDiagonalMoves(Piece* board[64], vector<int>& legal_moves);
  void getStraightMoves(Piece* board[64], vector<int>& legal_moves);
  bool isLegalMove(int square);
};

#endif