#ifndef PIECE_H
#define PIECE_H

#include <cctype>
#include <vector>

using namespace std;

struct Move {
  int row;
  int col;
};

class Piece {
 private:
  int row;
  int col;
  char name;
  bool is_white;
  bool has_moved;
  vector<Move> potential_moves;

 public:
  // Constructor and destructor
  Piece(int row, int col, char name);
  ~Piece();

  // Getters
  int getRow() { return row; }
  int getCol() { return col; }
  char getName() { return name; }
  bool getIsWhite() { return is_white; }
  bool getIsBlack() { return !is_white; }
  bool getHasMoved() { return has_moved; }
  vector<Move>& getPotentialMoves() { return potential_moves; }

  // Setters
  void setRow(int row) { this->row = row; }
  void setCol(int col) { this->col = col; }
  void setHasMoved(bool has_moved) { this->has_moved = has_moved; }
  void setPotentialMoves(vector<Move> potential_moves) {
    this->potential_moves = potential_moves;
  }

  // Virtual Methods
  virtual vector<Move> updateLegalMoves(vector<vector<Piece*>>& board) = 0;

  // Methods
  bool isSameColor(Piece* other);
  int colorOffset();
  bool isLegalMove(int row, int col);
  bool isPawn();
  bool isKing();
};

#endif
