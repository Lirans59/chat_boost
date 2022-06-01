#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include <iostream>
#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/container/map.hpp>
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
                  Session::session_ptr session);
    void removeSession(unsigned int id);

private:
    boost::asio::io_context&                        _io_contex;
    boost::asio::ip::tcp::acceptor                  _acceptor;
    boost::container::map<int, Session::session_ptr>_sessions;
    unsigned int                                    _session_count;
};

#endif // SERVER_HPP