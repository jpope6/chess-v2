#include "frame.h"

#include <iostream>
#include <wx/image.h>

using namespace std;

enum
{
    ID_Hello = 1
};

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Chess", wxDefaultPosition, wxSize(800, 837))
{
    chessboard = Board();
    chessboard.setBoardWithFenString(chessboard.getFenString());
    LoadChessPieces();

    Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    Bind(wxEVT_LEFT_DOWN, &MyFrame::OnMouseLeftDown, this);
    Bind(wxEVT_LEFT_UP, &MyFrame::OnMouseLeftUp, this);
}



void MyFrame::LoadChessPieces() {
    char pieceNames[] = {'b', 'k', 'n', 'p', 'q', 'r', 'B', 'K', 'N', 'P', 'Q', 'R'};

    for(char c : pieceNames) {
        wxBitmap bitmap;

        string path = "frame/images/";
        path += c;
        path += ".png";

        bool loadResult = bitmap.LoadFile(path, wxBITMAP_TYPE_PNG);
        if (loadResult) {
            wxImage image = bitmap.ConvertToImage();
            image.Rescale(100, 100, wxIMAGE_QUALITY_HIGH);
            bitmap = wxBitmap(image);

            getChessPieceBitmaps()[c] = bitmap;
        }
    }
}

void MyFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    wxSize sz = GetClientSize();
    wxCoord squareSize = sz.GetWidth() / 8; // Calculate the size of each square
    
    // Iterate over the chessboard squares
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            wxCoord x = col * squareSize;
            wxCoord y = row * squareSize;
            
            // Determine the color of the square based on row and column
            wxColour squareColor = (row + col) % 2 == 0 ? wxColour(185, 182, 174) : wxColour(75, 115, 153);

            dc.SetPen(*wxTRANSPARENT_PEN);
            dc.SetBrush(squareColor);
            
            // Draw the square
            wxRect squareRect(x, y, squareSize, squareSize);
            dc.DrawRectangle(squareRect);

            // Draw the chess piece
            if (chessboard.board[row][col] != ' ') {
                dc.DrawBitmap(getChessPieceBitmaps()[chessboard.board[row][col]], x, y, true);
            }
        }
    }
}

void MyFrame::OnMouseLeftDown(wxMouseEvent& event) {
    int mouseX = event.GetX();
    int mouseY = event.GetY();

    int squareSize = GetClientSize().GetWidth() / 8;

    int clickedCol = mouseX / squareSize;
    int clickedRow = mouseY / squareSize;

    // Check if a piece is present at the clicked position
    if (chessboard.board[clickedRow][clickedCol] != ' ') {
        pieceSelected = true;
        selectedPieceRow = clickedRow;
        selectedPieceCol = clickedCol;
    }
}

void MyFrame::OnMouseLeftUp(wxMouseEvent& event) {
    if (pieceSelected) {
        int mouseX = event.GetX();
        int mouseY = event.GetY();

        int squareSize = GetClientSize().GetWidth() / 8;

        int releasedCol = mouseX / squareSize;
        int releasedRow = mouseY / squareSize;

        chessboard.movePiece(selectedPieceRow, selectedPieceCol, releasedRow, releasedCol);
        Refresh();

        pieceSelected = false;
        selectedPieceRow = -1;
        selectedPieceCol = -1;
        
    }
}
 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}