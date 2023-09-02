#include "wx/wx.h"
#include <string>

//------------------------------------------------------------------------------
class TAcc : public wxFrame
{
public:
    TAcc(const wxString& title, const wxPoint& pos, const wxSize& size,
             long style = wxDEFAULT_FRAME_STYLE);
    void OnButtonClick(wxCommandEvent& evt);
    void Vir(wxCommandEvent& evt);
private:
    wxButton *Virement;
    std::vector<int> test;

    DECLARE_EVENT_TABLE()
};

enum{
    FIRST_BUTTON_ID = 2,
    BUTTON_VIREMENT = 10,
};
