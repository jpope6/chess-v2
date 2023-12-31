#ifndef FRAME_H
#define FRAME_H

#include <wx/bitmap.h>
#include <wx/dialog.h>
#include <wx/image.h>
#include <wx/wx.h>

#include <map>
#include <string>

#include "../board/board.h"

using namespace std;

class Frame : public wxFrame {
private:
  map<char, wxBitmap> chessPieceBitmaps;
  Board chessboard;

  wxDialog *promotionDialog;

  int mouse_x;
  int mouse_y;

  bool is_piece_selected;
  Piece *selected_piece;
  int selected_piece_square;

public:
  // Constructor
  Frame();

  // Member functions
  void loadChessPieces();
  void createPromotionDialog(wxDialog *dialog);

  // Drawing functions
  void onPaint(wxPaintEvent &event);
  void drawSquares(wxPaintDC &dc, int row, int col, wxCoord square_size);
  void drawInactivePiece(wxPaintDC &dc, int row, int col, wxCoord square_size);
  void drawActivePiece(wxPaintDC &dc);

  // Mouse events
  void onMouseLeftDown(wxMouseEvent &event);
  void onMouseLeftUp(wxMouseEvent &event);
  void onMouseMotion(wxMouseEvent &event);

  // Exit
  void onPromotionDialogClose(wxCloseEvent &event);
  void onExit(wxCommandEvent &event);

  DECLARE_EVENT_TABLE()
};

#endif
