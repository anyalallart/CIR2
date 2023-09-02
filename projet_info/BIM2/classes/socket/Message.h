//
// Created by benji on 20/11/2022.
//

#ifndef BIM_MESSAGE_H
#define BIM_MESSAGE_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <vector>
#include <memory>
#include <ostream>

#include "Connection.h"

enum class messageTypes: uint32_t
{
    ServerAccept,
    ClientAskConnection,
    ServerRespondAskConnection,

    ClientAskLogin,
    ServerRespondLogin,

    ClientAskAccount,
    ServerRespondAccount,

    ServerAskUpdate,
    ClientRespondUpdate
};

struct header {
    int ID;
    messageTypes type;
    uint32_t size = 0;
};

struct Message {
    header header;
    std::vector<uint8_t> body;

    size_t size() const
    {
        return body.size();
    }

    friend std::ostream& operator << (std::ostream& os, const Message& msg)
    {
        os << "Bank : " << std::to_string(msg.header.ID) << " Size : " << msg.header.size;
        return os;
    }

    friend Message& operator << (Message& msg, std::string& str)
    {
        size_t size = msg.body.size();

        std::vector vec(str.begin(), str.end());

        msg.body.resize(size + vec.size());

        msg.body.insert(msg.body.begin() + size, vec.begin(), vec.end());
        msg.header.size = msg.size();

        return msg;
    }

    friend Message& operator >> (Message& msg, std::string& str)
    {
        size_t i = msg.body.size() - sizeof(std::string);

        std::vector<uint8_t> vec;

        std::memcpy(&vec, msg.body.data() + i, sizeof(uint8_t));

        msg.body.resize(i);

        std::string new_str(vec.begin(), vec.end());

        str = new_str;

        msg.header.size = msg.body.size();

        return msg;
    }
};

class Connection;

struct InputMessage {
    std::shared_ptr<Connection> remote = nullptr;
    Message message;

    friend std::ostream& operator << (std::ostream& os, InputMessage& msg)
    {
        os << msg.message;
        return os;
    }
};
#endif //BIM_MESSAGE_H
