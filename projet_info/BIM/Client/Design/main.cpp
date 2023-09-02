#include "main.h"

BEGIN_EVENT_TABLE(TMyFrame, wxFrame)
                EVT_BUTTON(BUTTON_AG1,  TMyFrame::OnClick)
                EVT_BUTTON(BUTTON_AG2,  TMyFrame::OnClick)
                EVT_BUTTON(BUTTON_AG3,  TMyFrame::OnClick)
END_EVENT_TABLE()

IMPLEMENT_APP(TMyApp)

//------------------------------------------------------------------------------

bool TMyApp::OnInit() {
    TMyFrame *frame = new TMyFrame("Banque Isen Mondiale",
                                   wxPoint(150, 150), wxSize(480, 360));
    frame->Show(true);
    return (true);
}

//------------------------------------------------------------------------------
TMyFrame::TMyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
                   long style) : wxFrame(nullptr, -1, title, pos, size, style)
{

    Centre();
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    auto *txt = new wxStaticText(this, -1, _T("Bienvenu sur BIM"), wxPoint(180,20));


    Ag1 = new wxButton(this,BUTTON_AG1,"Agence 1", wxPoint(70,60),
                           wxDefaultSize);
    Ag2 = new wxButton(this,BUTTON_AG2,"Agence 2", wxPoint(190,60),
                           wxDefaultSize);
    Ag3 = new wxButton(this,BUTTON_AG3,"Agence 3", wxPoint(310,60),
                        wxDefaultSize);
}

//------------------------------------------------------------------------------
void TMyFrame::OnClick(wxCommandEvent& WXUNUSED(event)){
    Close();
    TCo *cone = new TCo("Banque Isen Mondiale",
                         wxPoint(150, 150), wxSize(480, 360));
    cone->Show(true);
}

//------------------------------------------------------------------------------
