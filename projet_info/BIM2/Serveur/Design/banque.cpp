#include "banque.h"

BEGIN_EVENT_TABLE(TMyFrame_agc, wxFrame)
                EVT_BUTTON(BUTTON_RECH,  TMyFrame_agc::Recherche)
END_EVENT_TABLE()

IMPLEMENT_APP(TMyAgc)

//------------------------------------------------------------------------------

bool TMyAgc::OnInit() {

    server.start();

    t2 = std::thread([&] {
        while(1)
        {
            DB database = *new DB("../database_serveur.db");

            std::this_thread::sleep_for(std::chrono::seconds(20));
            std::string request1 = "DELETE FROM client";
            std::string request2 = "DELETE FROM compte";
            std::string request3 = "DELETE FROM transaction";
            database.insert(request1);
            database.insert(request2);
            database.insert(request3);
            Message msg;
            msg.header.type = messageTypes::ServerAskUpdate;
            server.sendToAll(msg);
        }
    });

    t = std::thread([&] {
        while(1)
        {
            server.update(-1, false);
        }
    });

    TMyFrame_agc *frame = new TMyFrame_agc("Informations Clients",
                                   wxPoint(150, 150), wxSize(480, 360));
    frame->Show(true);
    return (true);
}

int TMyAgc::OnExit() {
    if (t.joinable()) {
        t.join();
    }

    if (t2.joinable()) {
        t2.join();
    }


    return 0;
}

//------------------------------------------------------------------------------

TMyFrame_agc::TMyFrame_agc(const wxString& title, const wxPoint& pos, const wxSize& size,
                   long style) : wxFrame(nullptr, -1, title, pos, size, style)
{
    Centre();
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    auto *txt = new wxStaticText(this, -1, _T("Bienvenue sur BIM pour les agences"), wxPoint(180,20));

    // wxStaticText pour la recherche
    auto *labelrech = new wxStaticText(this, -1, _T("Recherche client :"), wxPoint(160,70));

    // wxTextCtrl pour la recherche
    txt_rech = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(160,90), wxSize(250, wxDefaultSize.GetHeight()));

    // wxStaticText pour la recherche
    auto *labelrech_c = new wxStaticText(this, -1, _T("Recherche compte:"), wxPoint(160,120));

    // wxTextCtrl pour la recherche
    txt_rech_c = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(160,150), wxSize(250, wxDefaultSize.GetHeight()));


    rech = new wxButton(this,BUTTON_RECH,"Recherche", wxPoint(60, 90),
                       wxDefaultSize);
}


void TMyFrame_agc::Recherche(wxCommandEvent &event) {
    bool bOK = true;
    if (txt_rech->IsEmpty() && txt_rech_c->IsEmpty()) bOK = false;
    if (bOK){
        DB database = *new DB("../database_serveur.db");

        if (!txt_rech->IsEmpty()){
            std::string request = "SELECT * FROM client WHERE id='" + (std::string)txt_rech->GetValue() + "'";
            std::vector<std::map<std::string, std::string>> result = database.select(request);
            if (!result.empty())
            {
                auto user = result[0];
                wxMessageBox("Nom : " + user["nom"] + " Prenom : " + user["prenom"] + " Adresse mail : " + user["mail"] + " Numero de telephone : " + user["numero_tel"] + " Adresse : " + user["adresse"] + " Agence : " + user["ref_banque"],wxT("BIM"), wxICON_INFORMATION);
            }
        }

        if(!txt_rech_c->IsEmpty()){
            std::string request = "SELECT * FROM compte WHERE id='" + (std::string)txt_rech_c->GetValue() + "'";
            std::vector<std::map<std::string, std::string>> result = database.select(request);
            auto compte = result[0];

            if (!result.empty())
            {
                std::string request2 = "SELECT * FROM type_compte WHERE id='" + compte["type"] + "'";
                std::vector<std::map<std::string, std::string>> result2 = database.select(request2);

                if (!result2.empty())
                {
                    wxMessageBox("Solde : " + compte["solde"] + " Type de compte : " + result2[0]["nom"] + " Interet : " + result2[0]["interet"] + " % Agence : " + compte["ref_banque"],wxT("BIM"), wxICON_INFORMATION);
                }
            }
        }
    }
    else
        wxMessageBox(_T("Veuillez remplir une zone de recherche"),wxT("BIM"), wxICON_ERROR);
}
