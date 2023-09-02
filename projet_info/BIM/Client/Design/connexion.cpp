#include "connexion.h"
#include "crea.h"

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
    //txt_mdp = new wxPasswordEntryDialog( this, "Entrez votre mot de passe.", "Titre de la boîte de saisie.","", wxOK + wxCANCEL);

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
    if (bOK){
        //wxMessageBox( txt_mail->GetValue() << _T(" ") << txt_mdp->GetValue(),_T("test"));
        Close();
        TAcc *accueil = new TAcc("Choix compte",
                                wxPoint(150, 150), wxSize(480, 360));
        accueil->Show(true);
    }
    else
        int reponse = wxMessageBox(_T("Veuillez remplir les informations"),_T("NON"));
}

//------------------------------------------------------------------------------
void TCo::Creation(wxCommandEvent &event) {
    Close();
    TCrea_c *crea = new TCrea_c("Création compte",
                                        wxPoint(150, 150), wxSize(480, 360));
    crea->Show(true);
}

//------------------------------------------------------------------------------
