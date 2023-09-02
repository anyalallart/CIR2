#include "virement.h"


TVir::TVir(const wxString& title, const wxPoint& pos, const wxSize& size,
           long style) : wxFrame(nullptr, -1, title, pos, size, style) {

    Centre();

    Valider_vir = new wxButton(this, BUTTON_VALIDER_VIR, "Valider", wxPoint(20, 20),
                               wxDefaultSize);
    for (int i = 1; i < 4; i++) {
        auto *check = new wxCheckBox(this, CHECK_BOX, "Test", wxPoint(120, 120));
        check->Connect(
                CHECK_BOX + i,
                wxEVT_BUTTON,
                //wxCommandEventHandler(TAcc::OnButtonClick),
                nullptr,
                this);
        check->SetPosition(wxPoint(100, 50 * i));

        //Check = new wxCheckBox (this, CHECK_BOX, "Test", wxPoint(120,120));

        //Création d'une RadioBox.
        //radioBox = new wxRadioBox();
        //radioBox = new wxRadioBox(this, -1, "Liste de fruits", wxPoint(50, 10), wxDefaultSize, 1, array, wxRA_SPECIFY_COLS);


        /*radioBox->Connect(
                -1,
                wxEVT_COMMAND_RADIOBOX_SELECTED,
                wxCommandEventHandler(TVir::Validation),
                wxMessageBox("Félicitaion, vous avez choisi une " + radioBox->GetStringSelection())
                );
    */
    }
}

void TVir::Validation(wxCommandEvent &event) {

}
