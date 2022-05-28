#include "Session.hpp"

Session::Session(boost::asio::ip::tcp::socket& socket)
:   _socket(std::move(socket)),
    _message(std::move("This is Server\n"))
{
}
Session::Session(boost::asio::io_context& io_contex)
:   _socket(io_contex),
    _message(std::move("This is Server\n"))
{
}


boost::shared_ptr<Session> Session::create(boost::asio::io_context& io_contex)
{
    return boost::shared_ptr<Session>(new Session(io_contex));
}

void Session::write()
{
    std::cout << "sending message.." << std::endl;
    boost::asio::async_write(_socket, 
                    boost::asio::buffer(_message, _message.size()),
                    boost::bind(&Session::onWrite, this, boost::placeholders::_1));
}

void Session::onWrite(const boost::system::error_code& ec)
{
    std::cout << "message sent" << std::endl;
}

boost::asio::ip::tcp::socket& Session::getSocket()
{
    return _socket;
}

Session::~Session(){}