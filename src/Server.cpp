#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context)
:   _io_contex(io_context),
    _listener(io_context,
               std::bind(&Server::onAccept, this, // onAccept
                         std::placeholders::_1,
                         std::placeholders::_2),
               std::bind(&Server::onRead, this,   // onRead
                         std::placeholders::_1,
                         std::placeholders::_2,
                         std::placeholders::_3))
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

void Server::onRead(const boost::system::error_code& ec,
                std::size_t bytes_received, Session* session)
{
    if(!ec)
    {
        std::cout << bytes_received << "bytes received" << std::endl;
    }
    else
    {
        std::cout << "Connection closed" << std::endl;
        _session_manager.removeSession(session);
    }
    // session->read();
}

Server::~Server(){}