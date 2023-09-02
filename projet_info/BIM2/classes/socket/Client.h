//
// Created by benji on 20/11/2022.
//

#ifndef BIM_CLIENT_H
#define BIM_CLIENT_H

#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>

#include "Connection.h"
#include "Message.h"
#include "tsQueue.h"

using namespace boost::asio;

// TODO : Make client executable

// TODO : Inherit Agency

// TODO : Inherit User

class Client {
protected:
    io_context context;
    std::thread thrContext;
    std::unique_ptr<Connection> connection;

private:
    tsQueue<InputMessage> messageQueueIn;

public:
    Client()
    {}

    ~Client()
    {
        disconnect();
    }

    bool connect(const std::string& host, const uint16_t port)
    {
        try
        {
            ip::tcp::resolver resolver(context);
            ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

            connection = std::make_unique<Connection>(false, context, ip::tcp::socket(context), messageQueueIn);

            connection->connectToServer(endpoints);

            thrContext = std::thread([this]() { context.run(); });
        }
        catch (std::exception& e)
        {
            return false;
        }

        return true;
    }

    void disconnect()
    {
        if (isConnected())
        {
            connection->disconnect();
        }

        context.stop();

        if (thrContext.joinable())
        {
            thrContext.join();
        }

        connection.release();
    }

    bool isConnected()
    {
        return connection && connection->isConnected();
    }

    void send(const Message& msg)
    {
        if (isConnected())
        {
            connection->send(msg);
        }
    }

    tsQueue<InputMessage>& receive()
    {
        return messageQueueIn;
    }

    // TODO : Add Ping
    // TODO : Add Message All
};

#endif //BIM_CLIENT_H
