//
// Created by benji on 20/11/2022.
//

#ifndef BIM_SERVER_H
#define BIM_SERVER_H

#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>
#include <string>
#include <iostream>

#include <sqlite3.h>

#include "Connection.h"
#include "Message.h"
#include "tsQueue.h"
#include "../database/DB.h"

#include "wx/wx.h"

using namespace boost::asio;

// TODO : Make server executable

class Server {
protected:
    tsQueue<InputMessage> messageQueueIn;
    std::vector<std::shared_ptr<Connection>> validatedConnections;
    io_context context;
    std::thread thrContext;
    ip::tcp::acceptor acceptor;
    int uid = 10000;

public:
    Server(uint16_t port): acceptor(context, ip::tcp::endpoint(ip::tcp::v4(), port))
    {}

    ~Server()
    {
        stop();
    }

    bool start()
    {
        try
        {
            waitForClient();

            thrContext = std::thread([this]() { context.run(); });
        }
        catch (std::exception& e)
        {
            return false;
        }

        return true;
    }

    void stop()
    {
        context.stop();

        if (thrContext.joinable())
        {
            thrContext.join();
        }
    }

    void waitForClient()
    {
        acceptor.async_accept(
            [this](std::error_code ec, ip::tcp::socket socket)
            {
                if (!ec)
                {
                    std::shared_ptr<Connection> newConnection = std::make_shared<Connection>(true, context, std::move(socket), messageQueueIn);

                    if (onClientConnect(newConnection))
                    {
                        validatedConnections.push_back(std::move(newConnection));

                        validatedConnections.back()->connectToClient(uid++/* TODO: ADD UID FROM DATABASE */);
                    }

                }

                waitForClient();
            });
    }

    void sendToClient(std::shared_ptr<Connection> client, const Message& msg)
    {
        if (client && client->isConnected())
        {
            client->send(msg);
        }
        else
        {
            onClientDisconnect(client);

            client.reset();

            validatedConnections.erase(std::remove(validatedConnections.begin(), validatedConnections.end(), client), validatedConnections.end());
        }
    }

    void sendToAll(const Message& msg, std::shared_ptr<Connection> clientIgnored = nullptr)
    {
        bool hasInvalidClients = false;

        // Iterate through all clients in container
        for (auto& client : validatedConnections)
        {
            // Check client is connected...
            if (client && client->isConnected())
            {
                // ..it is!
                if(client != clientIgnored)
                    client->send(msg);
            }
            else
            {
                // The client couldnt be contacted, so assume it has
                // disconnected.
                onClientDisconnect(client);
                client.reset();

                // Set this flag to then remove dead clients from container
                hasInvalidClients = true;
            }
        }

        if (hasInvalidClients)
            validatedConnections.erase(
                    std::remove(validatedConnections.begin(), validatedConnections.end(), nullptr), validatedConnections.end());
    }

    void update(size_t maxMessages = -1, bool wait = false)
    {
        if (wait)
        {
            messageQueueIn.wait();
        }

        size_t messageCount = 0;

        while (messageCount < maxMessages && !messageQueueIn.empty())
        {
            auto msg = messageQueueIn.pop();

            onMessage(msg.remote, msg.message);

            messageCount++;
        }
    }

protected:
    bool onClientConnect(std::shared_ptr<Connection> client)
    {
        Message msg;

        msg.header.type = messageTypes::ServerAccept;
        client->send(msg);
        return true;
    }

    void onClientDisconnect(std::shared_ptr<Connection> client)
    {
        // TODO : Fill
    }

    void onMessage(const std::shared_ptr<Connection>& client, Message& msg)
    {
        DB database("../database_serveur.db");

        switch (msg.header.type) {
            case messageTypes::ClientAskConnection: {

                std::string agenceID = std::string(msg.body.begin(), msg.body.end() - 1);

                std::string sql = "SELECT * FROM banque WHERE id='" + agenceID + "'";

                std::vector<std::map<std::string, std::string>> result = database.select(sql);

                if (!result.empty())
                {
                    Message resp;
                    resp.header.type = messageTypes::ServerRespondAskConnection;
                    std::string payload = "1";
                    resp << payload;
                    client->send(resp);
                }
                else
                {
                    Message resp;
                    resp.header.type = messageTypes::ServerRespondAskConnection;
                    std::string payload = "0";
                    resp << payload;
                    client->send(resp);
                }

                break;
            }

            case messageTypes::ClientAskLogin: {
                std::string message = std::string(msg.body.begin(), msg.body.end() - msg.body.size()/2);

                std::vector<std::string> data;
                boost::split(data,message,boost::is_any_of("|"));

                std::string email = data[0];
                std::string password = data[1];

                std::string request = "SELECT * FROM client WHERE mail='" + email + "' AND mot_de_passe='" + password + "'";
                std::vector<std::map<std::string, std::string>> result = database.select(request);

                if (!result.empty())
                {
                    Message resp;
                    resp.header.type = messageTypes::ServerRespondLogin;
                    std::string payload = result[0]["ref_banque"];
                    resp << payload;
                    client->send(resp);
                }
                else
                {
                    Message resp;
                    resp.header.type = messageTypes::ServerRespondLogin;
                    std::string payload = "-1";
                    resp << payload;
                    client->send(resp);
                }
                break;
            }

            case messageTypes::ClientAskAccount: {
                std::string accountID = std::string(msg.body.begin(), msg.body.end() - 1);

                std::string request ="SELECT * FROM compte WHERE id='" + accountID + "'";
                std::vector<std::map<std::string, std::string>> result = database.select(request);

                if(!result.empty())
                {
                    Message resp;
                    resp.header.type = messageTypes::ServerRespondAccount;
                    std::string payload = result[0]["ref_banque"];
                    resp << payload;
                    client->send(resp);
                }
                else
                {
                    Message resp;
                    resp.header.type = messageTypes::ServerRespondAccount;
                    std::string payload = "-1";
                    resp << payload;
                    client->send(resp);
                }

                break;
            }

            case messageTypes::ClientRespondUpdate: {
                std::string raw_data = std::string(msg.body.begin(), msg.body.end() - msg.body.size()/2);
                std::vector<std::string> raw_data_vector;
                boost::split(raw_data_vector,raw_data,boost::is_any_of("%"));

                if(!raw_data_vector[0].empty()) {
                    std::string data1;
                    std::vector<std::string> result1;
                    boost::split(result1,raw_data_vector[0].substr(0, raw_data_vector[0].size()-1),boost::is_any_of("~"));

                    for (auto row1: result1) {
                        std::vector<std::string> result12;
                        boost::split(result12, row1, boost::is_any_of("|"));
                        std::string request =
                                "INSERT INTO client VALUES ('" + result12[0] + "','" + result12[1] + "','" +
                                result12[2] + "','" + result12[3] + "','" + result12[4] + "','" +
                                std::to_string(msg.header.ID) + "','" + result12[5] + "','" + result12[6] + "')";
                        database.insert(request);
                    }
                }

                if(!raw_data_vector[1].empty()) {
                    std::string data2;
                    std::vector<std::string> result2;
                    boost::split(result2,raw_data_vector[1].substr(0, raw_data_vector[1].size()-1),boost::is_any_of("~"));

                    for (auto row2: result2) {
                        std::vector<std::string> result22;
                        boost::split(result22, row2, boost::is_any_of("|"));
                        std::string request =
                                "INSERT INTO compte VALUES ('" + result22[0] + "','" + result22[1] + "','" +
                                std::to_string(msg.header.ID) + "','" + result22[2] + "','" + result22[3] + "')";
                        database.insert(request);
                    }
                }

                if(!raw_data_vector[2].empty()) {
                    std::string data3;
                    std::vector<std::string> result3;
                    boost::split(result3,raw_data_vector[2].substr(0, raw_data_vector[2].size()-1),boost::is_any_of("~"));

                    for (auto row3: result3) {
                        std::vector<std::string> result32;
                        boost::split(result32, row3, boost::is_any_of("|"));
                        std::string request =
                                "INSERT INTO `transaction` VALUES ('" + result32[0] + "','" + result32[1] + "','" +
                                result32[2] + "','" + result32[3] + "','" + result32[4] + "','" + result32[5] + "')";
                        database.insert(request);
                    }
                }
            }
        }
    }

};


#endif //BIM_SERVER_H
