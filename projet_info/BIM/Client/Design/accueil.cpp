#include "accueil.h"

BEGIN_EVENT_TABLE(TAcc, wxFrame)
                EVT_BUTTON(BUTTON_VIREMENT,  TAcc::Vir)
END_EVENT_TABLE()

TAcc::TAcc(const wxString& title, const wxPoint& pos, const wxSize& size,
                   long style) : wxFrame(nullptr, -1, title, pos, size, style) {

    Centre();
    auto *txt = new wxStaticText(this, -1, _T("Voici vos comptes :"), wxPoint(80,20));

    for (int i = 1; i < 4; i++) {
        auto* button = new wxButton(this, FIRST_BUTTON_ID+i);
        button->Connect(
                FIRST_BUTTON_ID+i,
                wxEVT_BUTTON,
                wxCommandEventHandler(TAcc::OnButtonClick),
                nullptr,
                this);
        button->SetPosition(wxPoint(100,50*i));

        //auto *vir = new wxStaticText(this, -1, _T("Virements"), wxPoint(300,20));

        Virement = new wxButton(this,BUTTON_VIREMENT,"Virement", wxPoint(300,80),
                                wxSize (100, 40));
    }
}

void TAcc::OnButtonClick(wxCommandEvent& evt) {
    //int buttonId = evt.GetId() - FIRST_BUTTON_ID;
    Close();
    TInf *info = new TInf("Info compte", wxPoint(150, 150), wxSize(480, 360));
    info->Show(true);
}

void TAcc::Vir(wxCommandEvent &evt) {
    Close();
    TVir *vir = new TVir("Virement",wxPoint(150, 150), wxSize(480, 360));
    vir->Show(true);
}





