#ifndef LISTENER_HPP
#define LISTENER_HPP

#pragma once

#define PORT 8085

#include <iostream>
#include "boost/asio.hpp"
#include "boost/bind.hpp"

class Listener
{
private:
    friend class Server;
    Listener(boost::asio::io_context& io_context);
    ~Listener();
    void start();
    void on_accpet(const boost::system::error_code& ec);
    
    
private:
    boost::asio::io_context&        _io_context;
    boost::asio::ip::tcp::acceptor  _acceptor;
    boost::asio::ip::tcp::socket    _socket;
};

#endif // LISTENER_HPP