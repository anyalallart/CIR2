#include "wx/wx.h"

#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <map>
#include "../../classes/socket/Server.h"

class TMyAgc : public wxApp
{
public:
    Server server = Server(8000);
    std::thread t;
    std::thread t2;
    virtual bool OnInit();
    virtual int OnExit();
};


DECLARE_APP(TMyAgc)

//------------------------------------------------------------------------------
class TMyFrame_agc : public wxFrame
{
public:
    TMyFrame_agc(const wxString& title, const wxPoint& pos, const wxSize& size,
             long style = wxDEFAULT_FRAME_STYLE);
    void Recherche(wxCommandEvent& event);

private:
    wxButton *rech;
    wxTextCtrl *txt_rech, *txt_rech_c;

DECLARE_EVENT_TABLE()
};

enum
{
    BUTTON_RECH = 1,
};
