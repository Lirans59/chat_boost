#ifndef SESSION_HPP
#define SESSION_HPP

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include "SessionManager.hpp"

class SessionManager;

class Session : public boost::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket& socket,
            SessionManager& sessin_manager);
    Session(boost::asio::io_context& io_contex,
            SessionManager& sessin_manager);
    ~Session();
    static boost::shared_ptr<Session> create(boost::asio::io_context& io_contex,
                            SessionManager& session_manager);
    void write();
    void read();
    boost::asio::ip::tcp::socket& getSocket();

private:
    void onWrite(const boost::system::error_code& ec);
    void onRead(const boost::system::error_code& ec,
                std::size_t bytes_received);

private:
    boost::asio::ip::tcp::socket    _socket;
    boost::asio::streambuf          _buffer;
    std::string                     _message;
    SessionManager&                 _session_manager;
};

#endif // SESSION_HPP