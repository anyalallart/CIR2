#include "include.h"
#include "../../classes/helpers/Client.h"


TInf::TInf(const wxString& title) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(520, 460))
{
    wxPanel *panel = new wxPanel(this, -1);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    helpers::Compte compte = wxGetApp().compte;

    std::string request2 ="SELECT * FROM type_compte WHERE id='" + std::to_string(compte.type) + "'";
    std::vector<std::map<std::string, std::string>> result2 = wxGetApp().database.select(request2);

    wxStaticBox *st = new wxStaticBox(panel, -1, wxT("Vos informations"),
                                      wxPoint(30, 15), wxSize(260, 150));

    auto *labelCompte = new wxStaticText(this, -1, _T("Compte numero " + std::to_string(compte.id)), wxPoint(110,50));

    auto *labelType = new wxStaticText(this, -1, _T("Votre type de compte :"), wxPoint(50,80));
    // Requete pour le prenom
    auto *labelTypeR = new wxStaticText(this, -1, result2[0]["nom"], wxPoint(180,80));

    wxStaticBox *sv = new wxStaticBox(panel, -1, wxT("Votre solde :"),
                                      wxPoint(30, 200), wxSize(260, 150));

    auto *txt1 = new wxStaticText(this, -1, std::to_string(compte.solde), wxPoint(130,240));

   auto *interet = new wxStaticText(this, -1, "Vos interets : " + result2[0]["interet"] + "%", wxPoint(100,280));


    wxStaticBox *sb = new wxStaticBox(panel, -1, wxT("Vos transactions"),
                                      wxPoint(310, 15), wxSize(160, 335));

    std::string request3 ="SELECT * FROM `transaction` WHERE `num_receveur`='" + std::to_string(compte.id) + "' OR `num_emetteur`='" + std::to_string(compte.id) + "' LIMIT 11";

    std::vector<std::map<std::string, std::string>> result3 = wxGetApp().database.select(request3);

    if(!result3.empty()) {
        for (int i = 0; i < result3.size(); i++) {
            std::string sign = stoi(result3[i]["num_receveur"]) == compte.id ? "+" : "-";
            std::string print = sign + " " + result3[i]["somme"] + " : " + result3[i]["libelle"];
            auto *txt = new wxStaticText(this, FIRST_BUTTON_ID + i, print);
            txt->SetPosition(wxPoint(330, 50 + (i * 25)));
        }
    }

    wxButton *retourButton = new wxButton(this, -1, wxT("Retour"),
                                      wxDefaultPosition, wxSize(120, 30));

    hbox->Add(retourButton, 1);

    vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    SetSizer(vbox);

    retourButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TInf::Button, this);

    Centre();
    ShowModal();
    Destroy();

}

void TInf::Button(wxCommandEvent &evt) {
    Close();
    TAcc *accueil = new TAcc("Vos comptes",
                             wxPoint(150, 150), wxSize(480, 360));
    accueil->Show(true);
}

