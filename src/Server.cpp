#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context)
:   _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT)),
    _socket(io_context),
    _io_contex(io_context)
{
    std::cout << "Server Ctor" << std::endl;
    doAccept();
}

void Server::doAccept()
{
    auto new_connection = Session::create(_io_contex);
    _acceptor.async_accept(new_connection->getSocket(), boost::bind(&Server::onAccept, this,
                            boost::asio::placeholders::error, new_connection));
}

void Server::onAccept(const boost::system::error_code& ec,
                    boost::shared_ptr<Session> session)
{
    if(!ec)
    {
        std::cout << "new connection" << std::endl;
        _sessions.push_back(session);
        _sessions.back()->write();
    }
    doAccept();
}

Server::~Server(){}