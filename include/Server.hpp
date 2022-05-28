#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Session.hpp"

#define PORT 8085

class Server
{
public:
    Server(boost::asio::io_context& io_context);
    ~Server();

private:
    void doAccept();
    void onAccept(const boost::system::error_code& ec,
                boost::shared_ptr<Session> session);

private:
    boost::asio::io_context&        _io_contex;
    boost::asio::ip::tcp::acceptor  _acceptor;
    boost::asio::ip::tcp::socket    _socket;
    std::vector< boost::shared_ptr<Session> >   _sessions;
};

#endif // SERVER_HPP