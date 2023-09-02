#include "../classes/socket/Server.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    Server server(8000);
    server.start();
    DB database("../database_serveur.db");

    auto res = std::async(std::launch::async, [&] {
        while(1)
        {
            std::this_thread::sleep_for(std::chrono::seconds(20));
            std::string request1 = "DELETE FROM client";
            std::string request2 = "DELETE FROM compte";
            std::string request3 = "DELETE FROM transaction";
            database.insert(request1);
            database.insert(request2);
            database.insert(request3);
            std::cout << "Sent update request" << std::endl;
            Message msg;
            msg.header.type = messageTypes::ServerAskUpdate;
            server.sendToAll(msg);
        }
    });
    while(1)
    {
        server.update(-1, false);
    }

    return 0;
}
