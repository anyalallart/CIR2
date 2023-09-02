//
// Created by Administrateur on 21/11/2022.
//
#include <iostream>

#include "../classes/socket/Client.h"
#include "../classes/socket/Message.h"
#include <windows.h>

using namespace std;
int main()
{
    Client client;

    client.connect("127.0.0.1", 8000);

    bool key[2] = { false, false };
    bool old_key[2] = { false, false };

    bool bQuit = false;
    while (!bQuit)
    {
        if (GetForegroundWindow() == GetConsoleWindow())
        {
            key[0] = GetAsyncKeyState(0x53);
            key[1] = GetAsyncKeyState(0x51);
        }

        if (key[0] && !old_key[0])
        {
            Message msg;
            msg.header.type = messageTypes::ClientAskConnection;
            std::string payload = "1";
            msg << payload;
            client.send(msg);
        }
        if (key[1] && !old_key[1]) bQuit = true;

        for (int i = 0; i < 3; i++) old_key[i] = key[i];
    }
    return 0;
}