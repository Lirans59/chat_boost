#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#pragma once

#include <iostream>
#include <cstring>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class Message : public boost::serialization::access
{
    friend class Client;
public:
    enum { body_max_size = 516 };
    Message(std::string&& str);
    ~Message();
    template<typename Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        ar & _header._op_code;
        ar & _header.body_size;
        ar & _body;
    }

private:
    typedef struct header
    {
        std::uint8_t _op_code;
        std::uint8_t body_size;
    }header_t;

private:
    header_t    _header;
    std::string _body;
};

#endif // MESSAGE_HPP