#ifndef SESSION_HPP
#define SESSION_HPP

#pragma once

#include <iostream>
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define SESSION_PORT 80
#define MESSAGE_SIZE 255

class Session // : Paeser
{
public:
    typedef boost::shared_ptr<Session> session_ptr;
    typedef std::function<void(unsigned int)> remove_ptr;
public:
    Session(boost::asio::io_context& io_context, unsigned int id,
            remove_ptr ptr);
    ~Session();

    void send();
    void recv();
    boost::asio::ip::tcp::socket& socket();

    static session_ptr create(boost::asio::io_context& io_context,
                              unsigned int id, remove_ptr ptr);

private:
    void onRecv(const boost::system::error_code& ec,
                std::size_t bytes_transfered);
    void onSend(const boost::system::error_code& ec);
    void onRecv();

private:
    boost::asio::io_context&        _io_context;
    boost::asio::ip::tcp::socket    _socket;
    std::string                     _message;
    unsigned int                    _session_id;
    remove_ptr                      _removeSession;
};

#endif // SESSION_HPP