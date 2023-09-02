#include <vector>
#include <map>
#include <string>
#include "wx/wx.h"

#include "../../classes/helpers/Client.h"


//------------------------------------------------------------------------------
class TCrea_c : public wxFrame
{
public:
    TCrea_c(const wxString& title, const wxPoint& pos, const wxSize& size,
             long style = wxDEFAULT_FRAME_STYLE);
    void OnQuit(wxCommandEvent& event);
    void Validation(wxCommandEvent& event);
    void Connexion(wxCommandEvent& event);
private:
    wxButton *Valider;
    wxButton *Quitter;
    wxButton *Conn;
    wxTextCtrl *txt_mail, *txt_mdp, *txt_pren, *txt_nom, *txt_adresse, *txt_tel;

DECLARE_EVENT_TABLE()
};

enum
{
    ID_TXT_PRENOM,
    ID_TXT_NOM,
    ID_TXT_ADRESSE,
    ID_TXT_TEL,
    ID_TXT_MAIL_CREA,
    ID_TXT_MDP_CREA,
};
