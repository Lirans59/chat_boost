#ifndef TRANSMITTER_HPP
#define TRANSMITTER_HPP

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>

class Transmitter
{
public:
    Transmitter(void *session);
    ~Transmitter();
    void send();

private:
    void onSend(const boost::system::error_code& ec,
                std::size_t bytes_transfered);

private:
    void                            *_session;
    std::ostringstream              _oarchive_stream;
    boost::archive::text_oarchive   _oarchive;
    std::string                     _buffer;

};

#endif // TRANSMITTER_HPP