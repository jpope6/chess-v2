#ifndef KING_H
#define KING_H

#include "../piece.h"

class King : public Piece {
private:
  bool is_in_check;

public:
  // Constructor
  King(int square, char piece);

  // Getters
  bool getIsInCheck() { return is_in_check; }

  // Virtual functions
  void updateLegalMoves(Piece *board[64]) override;

  // Member functions
  void checkPieceInPath(Piece *board[64], vector<int> &legal_moves);
  void setCastlingSquare(Piece *board[64], int rook_square,
                         vector<Piece *> &pieces_attacking_king);
  bool isInCheck(Piece *board[64], vector<Piece *> &pieces,
                 vector<Piece *> &pieces_attacking_king);
  bool isKingMovingThroughCheck(Piece *board[64], int to_square,
                                vector<Piece *> pieces_attacking_king);
};

#endif
