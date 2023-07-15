#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece {
 private:
  bool has_moved;

 public:
  // Constructor and destructor
  Pawn(int row, int col, char name, bool is_white);
  ~Pawn();

  // Getters
  bool getHasMoved() { return has_moved; }

  // Setters
  void setHasMoved(bool has_moved) { this->has_moved = has_moved; }

  // Virtual Methods
  // void updateLegalMoves() override;
};

#endif