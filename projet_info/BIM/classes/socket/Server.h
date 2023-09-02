//
// Created by benji on 20/11/2022.
//

#ifndef BIM_SERVER_H
#define BIM_SERVER_H

#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <vector>

#include "Connection.h"
#include "Message.h"
#include "tsQueue.h"

using namespace boost::asio;

// TODO : Make server executable

class Server {
protected:
    tsQueue<InputMessage> messageQueueIn;
    std::vector<std::shared_ptr<Connection>> validatedConnections;
    io_context context;
    std::thread thrContext;
    ip::tcp::acceptor acceptor;

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
            std::cerr << "Server : " << e.what() << "\n";
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

                        validatedConnections.back()->connectToClient(/* TODO: ADD UID FROM DATABASE */);
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
        // TODO : Fill
    }

    void onClientDisconnect(std::shared_ptr<Connection> client)
    {
        // TODO : Fill
    }

    void onMessage(std::shared_ptr<Connection> client, Message& msg)
    {
        // TODO : Fill
    }

};


#endif //BIM_SERVER_H
