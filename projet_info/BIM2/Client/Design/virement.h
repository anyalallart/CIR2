#include "wx/wx.h"

//------------------------------------------------------------------------------
class TVir : public wxDialog
{
public:
    TVir(const wxString& title);
    void OkButton(wxCommandEvent& evt);
    void Button(wxCommandEvent& evt);
private:
    wxTextCtrl *txt_iban, *txt_libelle, *txt_somme;
    std::vector<wxRadioButton*> buttons;
    std::vector<int> buttonsID;
};

enum{
    FIRST_ID = 3
};



