#include "include.h"

//------------------------------------------------------------------------------

BEGIN_EVENT_TABLE(TCo, wxFrame)
                EVT_BUTTON(BUTTON_VALIDER,  TCo::Validation)
                EVT_BUTTON(BUTTON_CREATION,  TCo::Creation)
                EVT_BUTTON(BUTTON_ANNULER,  TCo::OnQuit)
END_EVENT_TABLE()

//------------------------------------------------------------------------------
TCo::TCo(const wxString& title, const wxPoint& pos, const wxSize& size,
                   long style) : wxFrame(nullptr, -1, title, pos, size, style)
{
    //SetIcon(wxIcon(wxT("web.xpm")));
    Centre();
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Valider = new wxButton(this,BUTTON_VALIDER,"Valider", wxPoint(20,20),
                             wxDefaultSize);
    Quitter = new wxButton(this,BUTTON_ANNULER,"Quitter", wxPoint(20,60),
                              wxDefaultSize);
    Crea = new wxButton(this,BUTTON_CREATION,"Creation", wxPoint(20,100),
                           wxDefaultSize);

    // wxStaticText pour le mail
    auto *labelMail = new wxStaticText(this, -1, _T("Mail :"), wxPoint(160,20));

    // wxTextCtrl pour le mail
    txt_mail = new wxTextCtrl(this, ID_TXT_MAIL, _T(""), wxPoint(160,40), wxSize(250, wxDefaultSize.GetHeight()));

    // wxStaticText pour le mdp
    auto *labelMdp = new wxStaticText(this, -1, _T("Mot de passe :"), wxPoint(160,70));

    // wxTextCtrl pour le mdp
    txt_mdp = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(160,90), wxSize(250, wxDefaultSize.GetHeight()), wxTE_PASSWORD);

}

//------------------------------------------------------------------------------
void TCo::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    int reponse = wxMessageBox(_T("Annuler le formulaire ?"), // Message à afficher
                               _T("Confirmation"), // Titre de la boite de message
                               wxYES_NO | wxICON_QUESTION); // Style

    if (reponse == wxYES) // Si la réponse est positive,
        Close(true);          // on ferme la fenêtre

}

//------------------------------------------------------------------------------
void TCo::Validation(wxCommandEvent &event) {
    bool bOK = true;
    if (txt_mail->IsEmpty()) bOK = false;
    if (txt_mdp->IsEmpty()) bOK = false;
    if (bOK) {
        std::string request = "SELECT * FROM client WHERE mail='" + (std::string)txt_mail->GetValue() + "' AND mot_de_passe='" + (std::string)txt_mdp->GetValue() + "'";
        std::vector<std::map<std::string, std::string>> result = wxGetApp().database.select(request);
        if (!result.empty())
        {
            wxGetApp().user = helpers::Client(stoi(result[0]["id"]), result[0]["nom"], result[0]["prenom"], result[0]["adresse"], result[0]["numero_tel"], result[0]["mail"]);
            Close();
            TAcc *accueil = new TAcc("Choix compte", wxPoint(150, 150), wxSize(480, 360));
            accueil->Show(true);
        }
        else
        {
            Message msg;
            msg.header.type = messageTypes::ClientAskLogin;
            std::string payload = (std::string)txt_mail->GetValue() + "|" + (std::string)txt_mdp->GetValue();
            msg << payload;
            wxGetApp().client.send(msg);

            bool waitingResponse = true;

            while (waitingResponse)
            {
                if (!wxGetApp().client.receive().empty())
                {
                    auto msg = wxGetApp().client.receive().pop().message;
                    switch (msg.header.type)
                    {
                        case messageTypes::ServerRespondLogin:
                            if (stoi(std::string(msg.body.begin(), msg.body.end() - 1)) == -1)
                            {
                                wxMessageBox( wxT("Ce compte n'existe pas"), wxT("BIM"), wxICON_ERROR);
                                waitingResponse = false;
                            }
                            else
                            {
                                int newDB = stoi(std::string(msg.body.begin(), msg.body.end() - 1));
                                wxGetApp().database = *new DB("../database_client_" + std::to_string(newDB) + ".db");
                                wxGetApp().agence_id = newDB;
                                std::string request2 = "SELECT * FROM client WHERE mail='" + (std::string)txt_mail->GetValue() + "' AND mot_de_passe='" + (std::string)txt_mdp->GetValue() + "'";
                                std::vector<std::map<std::string, std::string>> result2 = wxGetApp().database.select(request);
                                if (!result2.empty()) {
                                    wxGetApp().user = helpers::Client(stoi(result2[0]["id"]), result2[0]["nom"], result2[0]["prenom"], result2[0]["adresse"], result2[0]["numero_tel"], result2[0]["mail"]);
                                    Close();
                                    TAcc *accueil = new TAcc("Choix compte", wxPoint(150, 150), wxSize(480, 360));
                                    accueil->Show(true);
                                }
                                waitingResponse = false;
                            }
                            break;
                    }
                }
            }

        }
    }
    else
        wxMessageBox(_T("Veuillez remplir les informations"),wxT("BIM"), wxICON_ERROR);
}

//------------------------------------------------------------------------------
void TCo::Creation(wxCommandEvent &event) {
    Close();
    TCrea_c *crea = new TCrea_c("Creation compte",
                                        wxPoint(150, 150), wxSize(480, 400));
    crea->Show(true);
}

//------------------------------------------------------------------------------
