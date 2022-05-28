#include "Listener.hpp"

Listener::Listener(boost::asio::io_context& io_context)
:   _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT)),
    _socket(io_context)
{
    std::cout << "Listener Ctor" << std::endl;
}

Listener::~Listener()
{
}

void Listener::start()
{
    _acceptor.async_accept(_socket, boost::bind(&Listener::onAccpet, this, 
                            boost::asio::placeholders::error));
}

void Listener::onAccpet(const boost::system::error_code& ec)
{
    std::cout << "Accepted connection" << std::endl;
}