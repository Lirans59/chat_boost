#include "Message.hpp"

Message::Message(std::string&& str)
:   _body(std::move(str))
{
}
Message::~Message()
{

}