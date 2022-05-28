#include "Server.hpp"
#include "Listener.hpp"

Server::Server(boost::asio::io_context& io_context)
: _listener(io_context)
{
    std::cout << "Server Ctor" << std::endl;
    _listener.start();
}

Server::~Server()
{

}