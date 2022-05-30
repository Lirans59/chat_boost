#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context)
:   _io_contex(io_context),
    _listener(io_context, _session_manager, std::bind(&Server::onAccept, this,
                                                      std::placeholders::_1,
                                                      std::placeholders::_2))
{
    std::cout << "Server Ctor" << std::endl;
}

void Server::onAccept(const boost::system::error_code& ec,
                      boost::shared_ptr<Session> session_ptr)
{
    if(!ec)
    {
        std::cout << "New connection" << std::endl;
        _session_manager.addSession(session_ptr);
        session_ptr->write();
        session_ptr->read();
    }
    _listener.doAccept();
}

Server::~Server(){}