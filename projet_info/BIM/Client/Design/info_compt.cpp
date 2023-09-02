#include "info_compt.h"


TInf::TInf(const wxString& title, const wxPoint& pos, const wxSize& size,
           long style) : wxFrame(nullptr, -1, title, pos, size, style) {

    Centre();
    auto *txt = new wxStaticText(this, -1, _T("Oui"), wxPoint(100,20));
}






