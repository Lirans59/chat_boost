#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include "Session.hpp"
#include "Message.hpp"
#include <boost/archive/text_iarchive.hpp>


class Receiver
{
public:
    Receiver(void *session);
    ~Receiver();


private:
    void doRecv();
    void onRecv(const boost::system::error_code& ec,
                std::size_t bytes_transfered);

private:
    void                            *_session;
    std::istringstream              _iarchive_stream;
    boost::archive::text_iarchive   _iarchive;
    std::string                     _buffer;
};

#endif // RECEIVER_HPP