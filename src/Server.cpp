#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context)
:   _io_contex(io_context),
    _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT)),
    _session_count(0)
{
    std::cout << "Server Ctor" << std::endl;
    doAccept();
}
Server::~Server(){}

void Server::doAccept()
{
    auto new_session = Session::create(_io_contex, _session_count,
                                       boost::bind(&Server::removeSession, this,
                                                boost::placeholders::_1));
    _acceptor.async_accept(new_session->socket(),
        boost::bind(&Server::onAccept, this,
                    boost::asio::placeholders::error,
                    new_session));
}

void Server::onAccept(const boost::system::error_code& ec,
                      Session::session_ptr session)
{
    if(!ec)
    {
        std::cout << "New connection" << std::endl;
        boost::asio::ip::tcp::endpoint remote_ep = session->socket().remote_endpoint();
        std::cout << "address:" << remote_ep.address() << std::endl <<
        "port:" << remote_ep.port() << std::endl;

        _sessions.emplace(_session_count, session);
        _session_count++;

        session->send();
        session->recv();
    }
    else
    {
        std::cout << "ERROR - accept" << std::endl;
    }
    doAccept();
}

void Server::removeSession(std::size_t id)
{
    _sessions.erase(id);
}