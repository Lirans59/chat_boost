#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include <iostream>
#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/container/map.hpp>
#include "Session.hpp"
#include "UserDB.hpp"

#define PORT 8085

class Server
{
public:
    static Server& get(boost::asio::io_context& io_context);
    Server(const Server&) = delete;
    const Server operator=(const Server&) = delete;

    ~Server();

private:
    Server(boost::asio::io_context& io_context);
    void doAccept();
    // onAccept add session to session pool
    void onAccept(const boost::system::error_code& ec,
                  Session::session_ptr session);
    void doRemoveSession(std::size_t id);
    void doBroadCast(std::size_t id);
    void onSend(const boost::system::error_code& ec, std::size_t id);
    void doAuthentication(Session *session);

private:
    boost::asio::io_context&                        _io_contex;
    boost::asio::ip::tcp::acceptor                  _acceptor;
    boost::container::map<int, Session::session_ptr>_session_pool;
    std::size_t                                     _session_count;
    UserDB                                          _db;
    callbacks_t                                     _callbacks;
};

#endif // SERVER_HPP