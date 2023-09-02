#include "include.h"

TVir::TVir(const wxString& title) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(480, 460))
{
    wxPanel *panel = new wxPanel(this, -1);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    wxStaticBox *st = new wxStaticBox(panel, -1, wxT("Vos comptes"),
                                      wxPoint(105, 15), wxSize(260, 150));

    std::string request ="SELECT * FROM compte WHERE client='"+ std::to_string(wxGetApp().user.id)+"'";
    std::vector<std::map<std::string, std::string>> result = wxGetApp().database.select(request);

    std::string request2 ="SELECT * FROM type_compte";
    std::vector<std::map<std::string, std::string>> type = wxGetApp().database.select(request2);

    for (int i = 0; i < result.size(); i++) {
        wxRadioButton* button = new wxRadioButton(panel,FIRST_ID+i,_T("Compte numero " + result[i]["id"] + ", " + type[stoi(result[i]["type"]) - 1]["nom"]));
        button->SetPosition(wxPoint(120,50+i*25));
        buttonsID.push_back(stoi(result[i]["id"]));
        buttons.push_back(button);
    }

    wxStaticBox *sv = new wxStaticBox(panel, -1, wxT("Choix du compte a crediter"),
                                      wxPoint(105, 200), wxSize(260, 150));

    auto *txt1 = new wxStaticText(this, -1, _T("Iban :"), wxPoint(120,240));

    txt_iban = new wxTextCtrl(panel, -1, wxT(""),
                                    wxPoint(175, 240));

    auto *txt2 = new wxStaticText(this, -1, _T("Libelle :"), wxPoint(120,280));

    txt_libelle = new wxTextCtrl(panel, -1, wxT(""),
                                    wxPoint(175, 280));

    auto *txt3 = new wxStaticText(this, -1, _T("Somme :"), wxPoint(120,320));

    txt_somme = new wxTextCtrl(panel, -1, wxT(""),
                          wxPoint(175, 320));

    wxButton *okButton = new wxButton(this, -1, wxT("Ok"),
                                      wxDefaultPosition, wxSize(100, 30));

    wxButton *retourButton = new wxButton(this, -1, wxT("Retour"),
                                          wxDefaultPosition, wxSize(160, 30));

    hbox->Add(okButton, 1);
    hbox->Add(retourButton, 1);

    vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    SetSizer(vbox);

    okButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TVir::OkButton, this);
    retourButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TVir::Button, this);

    Centre();
    ShowModal();

    Destroy();
}

void TVir::OkButton(wxCommandEvent &evt) {
    bool bOK = true;
    if (txt_iban->IsEmpty()) bOK = false;
    if (txt_libelle->IsEmpty()) bOK = false;
    if (txt_somme->IsEmpty()) bOK = false;
    if (bOK) {
        int accountIndex = -1;
        for (auto button: buttons) {
            if (button->GetValue()) {
                accountIndex = button->GetId() - FIRST_ID;
                break;
            }
        }

        int accountID = buttonsID[accountIndex];

        std::string request = "SELECT * FROM compte WHERE id='" + (std::string)txt_iban->GetValue() + "'";
        std::vector<std::map<std::string, std::string>> result = wxGetApp().database.select(request);

        std::string request2 = "SELECT solde FROM compte WHERE id='" + std::to_string(accountID) + "'";
        std::vector<std::map<std::string, std::string>> result2 = wxGetApp().database.select(request2);

        if (stoi((std::string)txt_somme->GetValue()) > stoi(result2[0]["solde"])) {
            wxMessageBox(wxT("Vous n'avez pas assez d'argent"), wxT("BIM"), wxICON_ERROR);
        }
        else {
            if (result.empty()) {
                Message msg;
                msg.header.type = messageTypes::ClientAskAccount;
                std::string payload = (std::string) txt_iban->GetValue();
                msg << payload;
                wxGetApp().client.send(msg);

                bool waitingResponse = true;

                while (waitingResponse) {
                    if (!wxGetApp().client.receive().empty()) {
                        auto msg = wxGetApp().client.receive().pop().message;
                        switch (msg.header.type) {
                            case messageTypes::ServerRespondAccount: {
                                int bankID = stoi(std::string(msg.body.begin(), msg.body.end() - 1));
                                if (bankID != -1) {
                                    time_t now = time(0);
                                    tm *ltm = localtime(&now);
                                    DB database2 = *new DB("../database_client_" + std::to_string(bankID) + ".db");
                                    std::string request3 =
                                            "INSERT INTO `transaction` (num_receveur, num_emetteur, somme, libelle, date) VALUES ('" +
                                            (std::string)txt_iban->GetValue() + "', '" + std::to_string(accountID) + "', '" +
                                            (std::string) txt_somme->GetValue() + "', '" +
                                            (std::string) txt_libelle->GetValue() + "', '" + std::to_string(1900 + ltm->tm_year) + "/" +
                                            std::to_string(ltm->tm_mon + 1) + "/" + std::to_string(ltm->tm_mday) + "')" ;

                                    std::string request4 =
                                            "UPDATE compte SET solde=solde-" + (std::string) txt_somme->GetValue() +
                                            " WHERE id='" + std::to_string(accountID) + "'";
                                    std::string request5 =
                                            "UPDATE compte SET solde=solde+" + (std::string) txt_somme->GetValue() +
                                            " WHERE id='" + (std::string)txt_iban->GetValue() + "'";

                                    wxGetApp().database.insert(request3);
                                    database2.insert(request3);
                                    wxGetApp().database.insert(request4);
                                    database2.insert(request5);

                                    waitingResponse = false;

                                    Close();
                                    TAcc *accueil = new TAcc("Vos comptes",
                                                             wxPoint(150, 150), wxSize(480, 360));
                                    accueil->Show(true);
                                } else {
                                    waitingResponse = false;
                                    wxMessageBox(wxT("Ce compte n'existe pas"), wxT("BIM"), wxICON_ERROR);
                                }
                            }
                        }
                    }
                }
            } else {
                time_t now = time(0);
                tm *ltm = localtime(&now);
                std::string request3 =
                        "INSERT INTO `transaction` (num_receveur, num_emetteur, somme, libelle, date) VALUES ('" +
                        result[0]["id"] + "', '" + std::to_string(accountID) + "', '" +
                        (std::string) txt_somme->GetValue() + "', '" + (std::string) txt_libelle->GetValue() +
                        "', '" + std::to_string(1900 + ltm->tm_year) + "/" +
                        std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(ltm->tm_mday) + "')";

                std::string request4 =
                        "UPDATE compte SET solde=solde-" + (std::string) txt_somme->GetValue() + " WHERE id='" +
                        std::to_string(accountID) + "'";
                std::string request5 =
                        "UPDATE compte SET solde=solde+" + (std::string) txt_somme->GetValue() + " WHERE id='" +
                        result[0]["id"] + "'";
                wxGetApp().database.insert(request3);
                wxGetApp().database.insert(request4);
                wxGetApp().database.insert(request5);
                Close();
                TAcc *accueil = new TAcc("Vos comptes",
                                         wxPoint(150, 150), wxSize(480, 360));
                accueil->Show(true);
            }
        }
    }
    else{
        wxMessageBox(wxT("Veuillez remplir les informations"), wxT("BIM"), wxICON_ERROR);
    }

}

void TVir::Button(wxCommandEvent &evt) {
    Close();
    TAcc *accueil = new TAcc("Vos comptes",
                             wxPoint(150, 150), wxSize(480, 360));
    accueil->Show(true);
}
