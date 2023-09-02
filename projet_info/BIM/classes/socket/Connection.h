//
// Created by benji on 20/11/2022.
//

#ifndef BIM_CONNECTION_H
#define BIM_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <iostream>

#include "Message.h"
#include "tsQueue.h"

using namespace boost::asio;

class Connection : public std::enable_shared_from_this<Connection> {
protected:
    ip::tcp::socket socket;
    io_context& context;
    tsQueue<Message> messagesOutQueue;
    tsQueue<InputMessage>& messagesInQueue;
    Message asyncMessageTmp;
    bool isServer;

    boost::uuids::uuid id{};


public:
    Connection(
            bool isServer,
            io_context& context,
            ip::tcp::socket socket,
            tsQueue<InputMessage>& queueIn
            ) : isServer(isServer), context(context), socket(std::move(socket)), messagesInQueue(queueIn)
    {}

    ~Connection()
    {
        disconnect();
    }

    boost::uuids::uuid getId()
    {
        return id;
    }

public:
    void connectToClient(boost::uuids::uuid uid)
    {
        if (isServer && socket.is_open())
        {
            id = uid;
            readHeader();
        }
    }

    void connectToServer(const ip::tcp::resolver::results_type& endpoints)
    {
        if(!isServer)
        {
            async_connect(socket, endpoints,
                [this](std::error_code ec, ip::tcp::endpoint endpoint)
                {
                    if(!ec)
                    {
                        readHeader();
                    }
                });
        }
    }

    void disconnect()
    {
        if (isConnected())
        {
            post(context, [this]() { socket.close(); });
        }
    }

    bool isConnected()
    {
        return socket.is_open();
    }

    void startListening()
    {

    }

    void send(const Message& msg)
    {
        post(context,
            [this, msg]()
            {
                bool isWritingMessages = !messagesOutQueue.empty();
                messagesOutQueue.push(msg);
                if (!isWritingMessages)
                    writeHeader();
            });
    }

private:
    void writeHeader()
    {
        async_write(socket, buffer(&messagesOutQueue.front().header, sizeof(header)),
            [this](std::error_code ec, size_t length)
            {
                if (!ec)
                {
                    if (!messagesOutQueue.front().body.empty())
                    {
                        writeBody();
                    }
                    else
                    {
                        messagesOutQueue.pop();

                        if (!messagesOutQueue.empty())
                        {
                            writeHeader();
                        }
                    }
                }
                else
                {
                    socket.close();
                }
            });
    }

    void writeBody()
    {
        async_write(socket, buffer(messagesOutQueue.front().body.data(), messagesOutQueue.front().body.size()),
            [this](std::error_code ec, size_t length)
            {
                if (!ec)
                {
                    messagesOutQueue.pop();
                    if (!messagesOutQueue.empty())
                    {
                        writeHeader();
                    }
                }
                else
                {
                    socket.close();
                }
            });
    }

    void readHeader()
    {
        async_read(socket, buffer(&asyncMessageTmp.header, sizeof(header)),
           [this](std::error_code ec, size_t length)
           {
                if (!ec)
                {
                    if (asyncMessageTmp.header.size > 0)
                    {
                        asyncMessageTmp.body.resize(asyncMessageTmp.header.size);
                        readBody();
                    }
                    else
                    {
                        addToInQueue();
                    }
                }
                else
                {
                    socket.close();
                }
           });
    }

    void readBody()
    {
        async_read(socket, buffer(asyncMessageTmp.body.data(), asyncMessageTmp.body.size()),
            [this](std::error_code ec, size_t length)
            {
                if (!ec)
                {
                    addToInQueue();
                }
                else
                {
                    socket.close();
                }
            });
    }

    void addToInQueue()
    {
        if (isServer)
        {
            messagesInQueue.push({ this->shared_from_this(), asyncMessageTmp });
        }
        else
        {
            messagesInQueue.push({ nullptr, asyncMessageTmp });
        }

        readHeader();
    }
};


#endif //BIM_CONNECTION_H
