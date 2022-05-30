#ifndef LISTENER_HPP
#define LISTENER_HPP

#pragma once

#include <iostream>
#include <functional>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "Session.hpp"
#include "SessionManager.hpp"

#define PORT 8085

class Listener
{
    friend class Server;
    typedef
    std::function<void(const boost::system::error_code& ec,
                       boost::shared_ptr<Session> session_ptr)>
    acceptFunPtr;
    typedef
    std::function<void(const boost::system::error_code& ec,
                       std::size_t bytes_transfered,
                       Session* session_ptr)>
    readFunPtr;

public:
    Listener(boost::asio::io_context& io_context,
             acceptFunPtr accept_func,
             readFunPtr read_func);
    ~Listener();

private:
    void doAccept();

private:
    boost::asio::io_context&        _io_context;
    boost::asio::ip::tcp::acceptor  _acceptor;
    acceptFunPtr                    _onAccept;
    readFunPtr                      _onRead;
};

#endif // LISTENER_HPP