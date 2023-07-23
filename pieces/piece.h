#ifndef PIECE_H
#define PIECE_H

#include <cctype>
#include <vector>

using namespace std;

struct Move {
  int row;
  int col;
};

enum Color { WHITE, BLACK };

class Piece {
 private:
  int row;
  int col;
  char name;
  bool is_white;
  Color color;
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
  Color getColor() { return color; }
  bool getIsWhite() { return this->color == WHITE; }
  bool getIsBlack() { return this->color == BLACK; }
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
  void getDiagonalMoves(vector<vector<Piece*>>& board, int row, int col,
                        vector<Move>& legal_moves);
  void getStraightMoves(vector<vector<Piece*>>& board, int row, int col,
                        vector<Move>& legal_moves);
  bool isSameColor(Piece* other);
  int colorOffset();
  bool isLegalMove(int row, int col);
  bool isPawn();
  bool isKing();

  vector<Move> getPathToKing(Piece* king);
};

#endif
