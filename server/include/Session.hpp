#ifndef SESSION_HPP
#define SESSION_HPP

#pragma once

#include <iostream>
#include <functional>
#include <queue>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Message.hpp"

#define MESSAGE_SIZE 512

class Session;
typedef struct callback
{
    std::function<void(std::size_t)> remove_func;
    std::function<void(std::size_t)> broad_cast_func;
    std::function<void(Session*)> auth_func;    
}callbacks_t;


class Session
{
    friend class Server;
public:
    typedef boost::shared_ptr<Session> session_ptr;
    typedef std::function<void(std::size_t)> remove_func;
    typedef std::function<void(std::size_t)> broad_cast_func;
    typedef std::function<void(Session*)> auth_func;
public:
    Session(boost::asio::io_context& io_context, std::size_t id,
            callbacks_t callbacks);
    ~Session();

    void send(std::string&& msg);
    void recv();
    void authenticate();
    boost::asio::ip::tcp::socket& socket();
    static session_ptr create(boost::asio::io_context& io_context,
                              std::size_t id, callbacks_t callbacks);

private:
    void onRecv(const boost::system::error_code& ec,
                std::size_t bytes_transfered);
    void onSend(const boost::system::error_code& ec);
    void onUsername(const boost::system::error_code& ec,
                std::size_t bytes_transfered);
    void onPassword(const boost::system::error_code& ec,
    std::size_t bytes_transfered);

    Message                         _chatMassage;
private:
    boost::asio::io_context&        _io_context;
    boost::asio::ip::tcp::socket    _socket;
    std::string                     _message;
    boost::asio::streambuf          _buf;
    std::queue<std::string>         _message_q;
    std::size_t                     _session_id;
    std::string                     _username;
    std::string                     _password;
    callbacks_t                     _callbacks;
};

#endif // SESSION_HPP