#ifndef FRAME_H
#define FRAME_H


#include <wx/wx.h>
#include <wx/bitmap.h>
#include <map>

#include "../board/board.h"

using namespace std;

class MyFrame : public wxFrame
{
public:
    MyFrame();

    // Getters
    map<char, wxBitmap>& getChessPieceBitmaps() { return chessPieceBitmaps; }
    Board& getBoard() { return chessboard; }
    int getSelectedPieceRow() { return selectedPieceRow; }
    int getSelectedPieceCol() { return selectedPieceCol; }

    void LoadChessPieces();
 
private:
    // variables
    map<char, wxBitmap> chessPieceBitmaps;
    Board chessboard; 
    bool pieceSelected;
    int selectedPieceRow;
    int selectedPieceCol;

    void OnPaint(wxPaintEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnMouseLeftDown(wxMouseEvent& event);
    void OnMouseLeftUp(wxMouseEvent& event);

    DECLARE_EVENT_TABLE()
};


#endif