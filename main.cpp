#include <wx/wx.h>

#include "frame/frame.h"

class App : public wxApp {
 public:
  bool OnInit() override;
};

bool App::OnInit() {
  Frame *frame = new Frame();
  frame->Show(true);
  return true;
}

wxIMPLEMENT_APP(App);

wxBEGIN_EVENT_TABLE(Frame, wxFrame) EVT_PAINT(Frame::onPaint)
    EVT_LEFT_DOWN(Frame::onMouseLeftDown) EVT_MOTION(Frame::onMouseMotion)
        wxEND_EVENT_TABLE()