#include "wx/wx.h"

//------------------------------------------------------------------------------
class TInf : public wxDialog
{
public:
    TInf(const wxString& title);
    void Button(wxCommandEvent& evt);
};

