#include "include.h"

BEGIN_EVENT_TABLE(TMyFrame, wxFrame)
                EVT_BUTTON(BUTTON_AG1,  TMyFrame::OnClick_1)
                EVT_BUTTON(BUTTON_AG2,  TMyFrame::OnClick_2)
                EVT_BUTTON(BUTTON_AG3,  TMyFrame::OnClick_3)
END_EVENT_TABLE()

IMPLEMENT_APP(TMyApp)

//------------------------------------------------------------------------------

bool TMyApp::OnInit() {
    client.connect("127.0.0.1", 8000);

    t2 = std::thread([&] {
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::seconds(60));
            std::string request2 ="SELECT * FROM compte";
            std::vector<std::map<std::string, std::string>> result2 = wxGetApp().database.select(request2);

            std::string request_types = "SELECT * FROM type_compte";
            std::vector<std::map<std::string, std::string>> types = wxGetApp().database.select(request_types);

            if (!result2.empty())
            {
                for (auto compte : result2)
                {
                    float interet = stof(types[stoi(compte["type"]) - 1]["interet"]);

                    float solde = stof(compte["solde"]) * (1.f + interet/100.f);

                    std::string updateSolde = "UPDATE compte SET solde='" + std::to_string(solde) + "' WHERE id='" + compte["id"] + "'";
                    wxGetApp().database.insert(updateSolde);
                }
            }
        }
    });

    t = std::thread([&] {
        while (wxGetApp().client.isConnected())
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            if (!wxGetApp().client.receive().empty())
            {
                auto msg = wxGetApp().client.receive().front().message;

                switch (msg.header.type)
                {
                    case messageTypes::ServerAskUpdate:
                        std::string buffer;
                        std::string request ="SELECT * FROM client";
                        std::vector<std::map<std::string, std::string>> result = wxGetApp().database.select(request);
                        if (!result.empty())
                        {
                            for (auto user : result)
                            {
                                buffer += user["id"] + "|" + user["nom"] + "|" + user["prenom"] + "|" + user["adresse"] + "|" + user["numero_tel"] + "|" + user["mail"] + "|" + user["mot_de_passe"] + "~";
                            }
                        }

                        buffer += "%";

                        std::string request2 ="SELECT * FROM compte";
                        std::vector<std::map<std::string, std::string>> result2 = wxGetApp().database.select(request2);

                        if (!result2.empty())
                        {
                            for (auto compte : result2)
                            {
                                buffer += compte["id"] + "|" + compte["client"] + "|" + compte["type"] + "|" + compte["solde"] + "~";
                            }
                        }

                        buffer += "%";

                        std::string request3 ="SELECT * FROM `transaction`";
                        std::vector<std::map<std::string, std::string>> result3 = wxGetApp().database.select(request3);
                        if (!result3.empty())
                        {
                            for (auto transaction : result3)
                            {
                                buffer += transaction["id"] + "|" + transaction["num_receveur"] + "|" + transaction["num_emetteur"] + "|" + transaction["somme"] + "|" + transaction["libelle"] + "|" + transaction["date"] + "~";
                            }
                        }

                        Message response;
                        response.header.ID = wxGetApp().agence_id;
                        response.header.type = messageTypes::ClientRespondUpdate;
                        response << buffer;
                        wxGetApp().client.send(response);
                        break;
                }
            }
        }
    });

    TMyFrame *frame = new TMyFrame("Banque Isen Mondiale",
                                   wxPoint(150, 150), wxSize(480, 360));
    frame->Show(true);
    return (true);
}

int TMyApp::OnExit(){
    if (t.joinable()) {
        t.join();
    }

    return 0;
}

//------------------------------------------------------------------------------
TMyFrame::TMyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
                   long style) : wxFrame(nullptr, -1, title, pos, size, style)
{
    Centre();
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    auto *txt = new wxStaticText(this, -1, _T("Bienvenu sur BIM"), wxPoint(180,20));


    Ag1 = new wxButton(this,BUTTON_AG1,"Agence 1", wxPoint(70,60),
                           wxDefaultSize);
    Ag2 = new wxButton(this,BUTTON_AG2,"Agence 2", wxPoint(190,60),
                           wxDefaultSize);
    Ag3 = new wxButton(this,BUTTON_AG3,"Agence 3", wxPoint(310,60),
                        wxDefaultSize);


}

//------------------------------------------------------------------------------
void TMyFrame::OnClick_1(wxCommandEvent& WXUNUSED(event)){
    if (wxGetApp().client.isConnected())
    {
        Message msg;
        msg.header.type = messageTypes::ClientAskConnection;
        std::string payload = "1";
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
                    case messageTypes::ServerRespondAskConnection:
                        if (stoi(std::string(msg.body.begin(), msg.body.end() - 1)) == 1)
                        {
                            wxGetApp().database = *new DB("../database_client_1.db");
                            wxGetApp().agence_id = 1;
                            Close();
                            TCo *cone = new TCo("Banque Isen Mondiale",wxPoint(150, 150), wxSize(480, 360));
                            cone->Show(true);
                        }
                        else
                        {
                            wxMessageBox( wxT("Agence introuvable"), wxT("BIM"), wxICON_ERROR);
                        }
                        waitingResponse = false;
                        break;
                }
            }
        }
    }
}

void TMyFrame::OnClick_2(wxCommandEvent &event) {
    if (wxGetApp().client.isConnected())
    {
        Message msg;
        msg.header.type = messageTypes::ClientAskConnection;
        std::string payload = "2";
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
                    case messageTypes::ServerRespondAskConnection:
                        if (stoi(std::string(msg.body.begin(), msg.body.end() - 1)) == 1)
                        {
                            wxGetApp().database = *new DB("../database_client_2.db");
                            wxGetApp().agence_id = 2;
                            Close();
                            TCo *cone = new TCo("Banque Isen Mondiale",wxPoint(150, 150), wxSize(480, 360));
                            cone->Show(true);
                        }
                        else
                        {
                            wxMessageBox( wxT("Agence introuvable"), wxT("BIM"), wxICON_ERROR);
                        }
                        waitingResponse = false;
                        break;
                }
            }
        }
    }
}

void TMyFrame::OnClick_3(wxCommandEvent &event) {
    if (wxGetApp().client.isConnected())
    {
        Message msg;
        msg.header.type = messageTypes::ClientAskConnection;
        std::string payload = "3";
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
                    case messageTypes::ServerRespondAskConnection:
                        if (stoi(std::string(msg.body.begin(), msg.body.end() - 1)) == 1)
                        {
                            wxGetApp().database = *new DB("../database_client_3.db");
                            wxGetApp().agence_id = 3;
                            Close();
                            TCo *cone = new TCo("Banque Isen Mondiale",wxPoint(150, 150), wxSize(480, 360));
                            cone->Show(true);
                        }
                        else
                        {
                            wxMessageBox( wxT("Agence introuvable"), wxT("BIM"), wxICON_ERROR);
                        }
                        waitingResponse = false;
                        break;
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
