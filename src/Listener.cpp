#include "Listener.hpp"

Listener::Listener(boost::asio::io_context& io_context)
:   _io_context(io_context),
    _socket(_io_context),
    _acceptor(_io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT))
{
    std::cout << "Listener Ctor" << std::endl;
}

Listener::~Listener()
{
}

void Listener::start()
{
    _acceptor.async_accept(_socket, boost::bind(&Listener::on_accpet, this, 
                            boost::asio::placeholders::error));
}

void Listener::on_accpet(const boost::system::error_code& ec)
{
    std::cout << "Accepted connection" << std::endl;
}