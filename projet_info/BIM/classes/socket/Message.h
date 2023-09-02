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

};

struct header {
    boost::uuids::uuid ID;
    messageTypes type;
    uint32_t size;
};

struct Message {
    header header;
    std::vector<std::string> body;

    size_t size() const
    {
        return sizeof(header) + body.size();
    }

    friend std::ostream& operator << (std::ostream& os, const Message& msg)
    {
        os << "Bank : " << boost::uuids::to_string(msg.header.ID) << " Size : " << msg.header.size;
        return os;
    }

    friend Message& operator << (Message& msg, std::string& str)
    {
        size_t i = msg.body.size();
        msg.body.resize(i + sizeof(std::string));

        std::memcpy(msg.body.data() + i, &str, sizeof(std::string));

        msg.header.size = msg.size();

        return msg;
    }

    friend Message& operator >> (Message& msg, std::string& str)
    {
        size_t i = msg.body.size() - sizeof(std::string);

        std::memcpy(&str, msg.body.data() + i, sizeof(std::string));

        msg.body.resize(i);

        msg.header.size = msg.size();

        return msg;
    }
};

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
