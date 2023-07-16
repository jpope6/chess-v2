#ifndef FRAME_H
#define FRAME_H

#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/wx.h>

#include <map>

#include "../board/board.h"

using namespace std;

class MyFrame : public wxFrame {
 public:
  // Constructor
  MyFrame();

  // Getters
  map<char, wxBitmap> &getChessPieceBitmaps() { return chessPieceBitmaps; }
  Board &getBoard() { return chessboard; }
  int getSelectedPieceRow() { return selectedPieceRow; }
  int getSelectedPieceCol() { return selectedPieceCol; }

  // Member functions
  void LoadChessPieces();

 private:
  // variables
  map<char, wxBitmap> chessPieceBitmaps;
  Board chessboard;
  bool pieceSelected;
  Piece *selectedPiece;
  int selectedPieceRow;
  int selectedPieceCol;

  int mouseX;
  int mouseY;

  // Member functions
  void drawActivePiece(wxPaintDC &dc);
  void drawInactivePiece(wxPaintDC &dc, int row, int col, wxCoord squareSize);
  void drawSquares(wxPaintDC &dc, int row, int col, wxSize size,
                   wxCoord squareSize);
  void OnPaint(wxPaintEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnMouseLeftDown(wxMouseEvent &event);
  void OnMouseLeftUp(wxMouseEvent &event);
  void OnMouseMotion(wxMouseEvent &event);

  DECLARE_EVENT_TABLE()
};

#endif