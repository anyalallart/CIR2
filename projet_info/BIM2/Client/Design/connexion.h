#include "wx/wx.h"

//------------------------------------------------------------------------------
class TCo : public wxFrame
{
public:
    TCo(const wxString& title, const wxPoint& pos, const wxSize& size,
             long style = wxDEFAULT_FRAME_STYLE);
    void OnQuit(wxCommandEvent& event);
    void Validation(wxCommandEvent& event);
    void Creation(wxCommandEvent& event);
private:
    wxButton *Valider;
    wxButton *Quitter;
    wxButton *Crea;
    wxTextCtrl *txt_mail, *txt_mdp;

    DECLARE_EVENT_TABLE()
};

enum
{
    BUTTON_VALIDER = 1,
    BUTTON_ANNULER = 2,
    BUTTON_CREATION = 3,
    ID_TXT_MAIL,
    ID_TXT_MDP,
};
