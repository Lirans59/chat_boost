#ifndef SESSION_HPP
#define SESSION_HPP

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

class Session : public boost::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket& socket);
    Session(boost::asio::io_context& io_contex);
    ~Session();
    static boost::shared_ptr<Session> create(boost::asio::io_context& io_contex);
    void write();
    void read();
    boost::asio::ip::tcp::socket& getSocket();

private:
    void onWrite(const boost::system::error_code& ec);

private:
    boost::asio::ip::tcp::socket    _socket;
    std::string                     _message;
};

#endif // SESSION_HPP