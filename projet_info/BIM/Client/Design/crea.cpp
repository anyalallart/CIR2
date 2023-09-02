#include "crea.h"
#include "connexion.h"

BEGIN_EVENT_TABLE(TCrea_c, wxFrame)
                EVT_BUTTON(BUTTON_VALIDER,  TCrea_c::Validation)
                EVT_BUTTON(BUTTON_CREATION,  TCrea_c::Connexion)
                EVT_BUTTON(BUTTON_ANNULER,  TCrea_c::OnQuit)
END_EVENT_TABLE()

//------------------------------------------------------------------------------
TCrea_c::TCrea_c(const wxString& title, const wxPoint& pos, const wxSize& size,
                   long style) : wxFrame(nullptr, -1, title, pos, size, style)
{
    Centre();
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Valider = new wxButton(this,BUTTON_VALIDER,"Valider", wxPoint(20,20),
                           wxDefaultSize);
    Quitter = new wxButton(this,BUTTON_ANNULER,"Quitter", wxPoint(20,60),
                           wxDefaultSize);
    Conn = new wxButton(this,BUTTON_CREATION,"Connexion", wxPoint(20,100),
                        wxDefaultSize);

    auto *labelPrenom = new wxStaticText(this, -1, _T("Prénom :"), wxPoint(160,20));

    // wxTextCtrl pour le prenom
    txt_pren = new wxTextCtrl(this, ID_TXT_PRENOM, _T(""), wxPoint(160,40));

    auto *labelNom = new wxStaticText(this, -1, _T("Nom :"), wxPoint(160,70));

    // wxTextCtrl pour le nom
    txt_nom = new wxTextCtrl(this, ID_TXT_NOM, _T(""), wxPoint(160,90));

    auto *labelAdresse = new wxStaticText(this, -1, _T("Adresse :"), wxPoint(160,120));

    // wxTextCtrl pour le adresse
    txt_adresse = new wxTextCtrl(this, ID_TXT_ADRESSE, _T(""), wxPoint(160,140));

    auto *labelTel = new wxStaticText(this, -1,  _("Numéro de téléphone :"), wxPoint(160,170));

    // wxTextCtrl pour le tel
    txt_tel = new wxTextCtrl(this, ID_TXT_TEL, _T(""), wxPoint(160,190));

    auto *labelMail = new wxStaticText(this, -1, _T("Mail :"), wxPoint(160,220));

    // wxTextCtrl pour le mail
    txt_mail = new wxTextCtrl(this, ID_TXT_MAIL_CREA, _T(""), wxPoint(160,240));

    // wxStaticText pour le mdp
    auto *labelMdp = new wxStaticText(this, -1, _T("Mot de passe:"), wxPoint(160,270));

    // wxTextCtrl pour le mdp
    txt_mdp = new wxTextCtrl(this, ID_TXT_MDP_CREA, _T(""), wxPoint(160,290));
}


//------------------------------------------------------------------------------
void TCrea_c::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    int reponse = wxMessageBox(_T("Annuler le formulaire ?"), // Message à afficher
                               _T("Confirmation"), // Titre de la boite de message
                               wxYES_NO | wxICON_QUESTION); // Style

    if (reponse == wxYES) // Si la réponse est positive,
        Close(true);          // on ferme la fenêtre

}

//------------------------------------------------------------------------------
void TCrea_c::Validation(wxCommandEvent &event) {
    bool bOK = true;
    if (txt_mail->IsEmpty()) bOK = false;
    if (txt_mdp->IsEmpty()) bOK = false;
    if (bOK) {
        //wxMessageBox(txt_mail->GetValue() << _T(" ") << txt_mdp->GetValue(), _T("test"));
        Close();
        TAcc *accueil = new TAcc("Choix compte",wxPoint(150, 150), wxSize(480, 360));
        accueil->Show(true);
    }
    else
        int reponse = wxMessageBox(_T("Veuillez remplir les informations"),_T("NON"));
}

//------------------------------------------------------------------------------
void TCrea_c::Connexion(wxCommandEvent &event) {
    Close();
    TCo *frame = new TCo("Banque Isen Mondiale",
                                   wxPoint(150, 150), wxSize(480, 360));
    frame->Show(true);
}

//------------------------------------------------------------------------------