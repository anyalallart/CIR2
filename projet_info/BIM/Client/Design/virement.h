#include "wx/wx.h"

//------------------------------------------------------------------------------
class TVir : public wxFrame
{
public:
    TVir(const wxString& title, const wxPoint& pos, const wxSize& size,long style = wxDEFAULT_FRAME_STYLE);
    void Validation(wxCommandEvent& event);
private :
    wxButton *Valider_vir;
    wxCheckBox *Check;
    wxPanel *panel;
    wxRadioBox *radioBox;

    wxArrayString array;
};

enum
{
    BUTTON_VALIDER_VIR = 1,
    CHECK_BOX = 2,
};

