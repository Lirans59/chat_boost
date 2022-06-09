#include "Message.hpp"

Message::Message(std::uint8_t op_code, std::uint8_t data_size, char **data) 
:   _op_code(op_code), _data_size(data_size), _data(*data)
{
    *data = nullptr;
}
Message::Message(){}

Message::~Message()
{
    delete _data;
}