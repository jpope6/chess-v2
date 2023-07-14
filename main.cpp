#include <wx/wx.h>

#include "./frame/frame.h"

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 
wxIMPLEMENT_APP(MyApp);

wxBEGIN_EVENT_TABLE(MyFrame,wxFrame)
    EVT_PAINT(MyFrame::OnPaint)
    EVT_LEFT_DOWN(MyFrame::OnMouseLeftDown)
    EVT_LEFT_UP(MyFrame::OnMouseLeftUp)
wxEND_EVENT_TABLE()