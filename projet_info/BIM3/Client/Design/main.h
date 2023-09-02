#include "wx/wx.h"
#include <iostream>
#include "../../classes/helpers/Client.h"
#include "../../classes/database/DB.h"
#include "../../classes/socket/Client.h"
#include "../../classes/socket/Message.h"
#include <chrono>
#include <thread>
#include <vector>
//------------------------------------------------------------------------------
class TMyApp : public wxApp
{
public:
    Client client;
    DB database;
    helpers::Client user;
    helpers::Compte compte;
    std::thread t;
    std::thread t2;
    int agence_id;
    virtual bool OnInit();
    virtual int OnExit();
};

DECLARE_APP(TMyApp)

//------------------------------------------------------------------------------
class TMyFrame : public wxFrame
{
public:
    TMyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
             long style = wxDEFAULT_FRAME_STYLE);
    void OnClick_1(wxCommandEvent& event);
    void OnClick_2(wxCommandEvent& event);
    void OnClick_3(wxCommandEvent& event);

private:
    wxButton *Ag1;
    wxButton *Ag2;
    wxButton *Ag3;

DECLARE_EVENT_TABLE()
};

enum
{
    BUTTON_AG1 = 1,
    BUTTON_AG2 = 2,
    BUTTON_AG3 = 3,
};
