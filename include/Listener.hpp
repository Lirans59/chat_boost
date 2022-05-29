#ifndef LISTENER_HPP
#define LISTENER_HPP

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "Session.hpp"
#include "SessionManager.hpp"

#define PORT 8085

class Listener
{
public:
    Listener(boost::asio::io_context& io_context,
                       SessionManager& session_manager);
    ~Listener();

private:
    void doAccept();
    //maybe pass shared_ptr by reference ??
    void onAccept(const boost::system::error_code& ec,
                  boost::shared_ptr<Session> session_ptr);

private:
    boost::asio::io_context&        _io_context;
    boost::asio::ip::tcp::acceptor  _acceptor;
    SessionManager&                 _session_manager;
};

#endif // LISTENER_HPP