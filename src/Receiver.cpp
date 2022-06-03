#include "Receiver.hpp"

Receiver::Receiver(void *session)
:   _iarchive(_iarchive_stream), _session(session)
{
    doRecv();
}

Receiver::~Receiver(){}

void Receiver::doRecv()
{
    //read header
    static_cast<Session*>(_session)->socket().async_receive(boost::asio::buffer(_buffer, Message::HEADER_SIZE), 0,
        boost::bind(&Receiver::onRecv, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Receiver::onRecv(const boost::system::error_code& ec, std::size_t bytes_transfered)
{
    if(!ec && bytes_transfered == 4)
    {
        std::cout << "Header read successfully" << std::endl;
        //read body
        static_cast<Session*>(_session)->socket().async_receive(boost::asio::buffer(_buffer, Message::HEADER_SIZE), 0,
            boost::bind(&Receiver::onRecv, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        _iarchive_stream.str() = _buffer;
        static_cast<Session*>(_session)->send();
    }
}