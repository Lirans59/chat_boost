#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context)
:   _io_contex(io_context),
    _listener(io_context, _session_manager)
{
    std::cout << "Server Ctor" << std::endl;
}

Server::~Server(){}