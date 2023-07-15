#ifndef PIECE_H
#define PIECE_H

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
  vector<Move> potential_moves;  // [row, col
  vector<Move> legal_moves;

 public:
  // Constructor and destructor
  Piece(int row, int col, char name, bool is_white);
  ~Piece();

  // Getters
  int getRow() { return row; }
  int getCol() { return col; }
  char getName() { return name; }
  bool getIsWhite() { return is_white; }
  vector<Move> getPotentialMoves() { return potential_moves; }
  vector<Move> getLegalMoves() { return legal_moves; }

  // Setters
  void setRow(int row) { this->row = row; }
  void setCol(int col) { this->col = col; }
  void setPotentialMoves(vector<Move> potential_moves) {
    this->potential_moves = potential_moves;
  }
  void setLegalMoves(vector<Move> legal_moves) {
    this->legal_moves = legal_moves;
  }

  // Virtual Methods
  // virtual void updateLegalMoves();

  // Methods
  bool isSameColor(Piece* other);
};

#endif
