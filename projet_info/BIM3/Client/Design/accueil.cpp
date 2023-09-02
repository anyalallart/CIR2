#include "include.h"
#include <algorithm>

#include "../../classes/helpers/Client.h"

BEGIN_EVENT_TABLE(TAcc, wxFrame)
                EVT_BUTTON(BUTTON_VIREMENT,  TAcc::Vir)
END_EVENT_TABLE()

TAcc::TAcc(const wxString& title, const wxPoint& pos, const wxSize& size,
                   long style) : wxFrame(nullptr, -1, title, pos, size, style) {

    Centre();
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

    auto *txt = new wxStaticText(this, -1, _T("Voici vos comptes :"), wxPoint(80,20));


    std::string request ="SELECT * FROM compte WHERE client='"+ std::to_string(wxGetApp().user.id)+"'";
    std::vector<std::map<std::string, std::string>> result = wxGetApp().database.select(request);

    std::string request2 ="SELECT * FROM type_compte";
    std::vector<std::map<std::string, std::string>> result2 = wxGetApp().database.select(request2);

    for (int i = 0; i < result.size(); i++) {
        auto* button = new wxButton(this, FIRST_BUTTON_ID+i,result2[stoi(result[i]["type"])-1]["nom"]);
        button->Connect(
                FIRST_BUTTON_ID+i,
                wxEVT_BUTTON,
                wxCommandEventHandler(TAcc::OnButtonClick),
                nullptr,
                this);
        button->SetPosition(wxPoint(80,50*(i+1)));
        test.push_back(stoi(result[i]["id"]));
    }
    Virement = new wxButton(this,BUTTON_VIREMENT,"Virement", wxPoint(300,80),
                            wxSize (100, 40));
}

void TAcc::OnButtonClick(wxCommandEvent& evt) {

    std::string request ="SELECT * FROM compte WHERE id='" + std::to_string(test[evt.GetId() - FIRST_BUTTON_ID]) + "'";
    std::vector<std::map<std::string, std::string>> result = wxGetApp().database.select(request);
    wxGetApp().compte = helpers::Compte(stoi(result[0]["id"]), wxGetApp().user.id, stoi(result[0]["type"]), stof(result[0]["solde"]));

    Close();
    TInf *info = new TInf("Informations compte");
    info->Show(true);

}

void TAcc::Vir(wxCommandEvent &evt) {
    Close();
    TVir *vir = new TVir("Virement");
    vir->Show(true);
}
