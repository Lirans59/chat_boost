#ifndef CLIENT_HPP
#define CLIENT_HPP

#pragma once

#include <iostream>
#include <queue>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Message.hpp"

#define PORT 8085

class Client
{
public:
    Client(boost::asio::io_context& io_context);
    ~Client();

private:
    void doRecv();
    void onRecv(const boost::system::error_code& ec,
        std::size_t bytes_transfered);
    void doConnect();
    void onConnect(const boost::system::error_code& ec);
    void doSend();
    void onSend(const boost::system::error_code& ec);
    void getInput();

private:
    boost::asio::io_context&        _io_context;
    boost::asio::ip::tcp::socket    _socket;
    std::queue<std::string>             _message_q; //change to q of Message instead of string
    boost::asio::streambuf          _buf;
    std::uint8_t                    _internal_flag;
};

#endif // CLIENT_HPP