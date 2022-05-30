#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Listener.hpp"
#include "Session.hpp"

#define PORT 8085

class Server
{
public:
    Server(boost::asio::io_context& io_context);
    ~Server();

private:
    void onAccept(const boost::system::error_code& ec,
                  boost::shared_ptr<Session> session_ptr);

private:
    boost::asio::io_context&    _io_contex;
    Listener                    _listener;
    SessionManager              _session_manager;
};

#endif // SERVER_HPP