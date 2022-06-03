#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#pragma once

#include <cstring>
#include <iostream>
#include <cstring>
#include <boost/serialization/access.hpp>

// #define HEADER_SIZE     2
// #define BODY_MAX_SIZE   255

class Message
{
    friend class boost::serialization::access;
    friend class Transmitter;
public:
    enum{ HEADER_SIZE = 2 };
    enum{ BODY_MAX_SIZE = 255 };
    Message(std::uint8_t op_code, std::uint8_t data_size, char **data);
    Message();
    ~Message();
private:
    template<typename archive>
    void serialize(archive& ar, unsigned int version)
    {
        ar & _op_code;
        ar & _data_size;
        for(auto i= 0; i < _data_size + 1; i++){
            ar & _data[i];
        }
    }
    
private:
    std::uint8_t    _op_code;
    std::uint8_t    _data_size;
    char*           _data;
};

#endif // MESSAGE_HPP