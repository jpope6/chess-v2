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
  map<int, vector<int>> path_map;
  map<int, int[8]> num_squares_to_edge;

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
  bool getHasMoved() { return has_moved; }
  vector<int> getLegalMoves() { return legal_moves; }
  map<int, vector<int>> getPathMap() { return path_map; }

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
  void numSquaresToEdge();
  void getDiagonalMoves(Piece* board[64], vector<int>& legal_moves);
  void getStraightMoves(Piece* board[64], vector<int>& legal_moves);
  bool isLegalMove(int square);
  vector<int> getPathToKing(Piece* board[64], Piece* king);

  bool isPawn() { return piece_type == PAWN; }
  bool isRook() { return piece_type == ROOK; }
  bool isKing() { return piece_type == KING; }
};

#endif