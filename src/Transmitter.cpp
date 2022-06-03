#include "Transmitter.hpp"
#include "Session.hpp"

Transmitter::Transmitter(void *session)
:   _session(session), _oarchive(_oarchive_stream)
{
    send();
}

Transmitter::~Transmitter()
{

}

void Transmitter::send()
{
    strcpy(static_cast<Session*>(_session)->_chatMassage._data, "YES THIS IS DOG");
    static_cast<Session*>(_session)->_chatMassage._data_size = 16;
    _oarchive << static_cast<Session*>(_session)->_chatMassage;
    std::cout << _oarchive_stream.str() << std::endl;
    static_cast<Session*>(_session)->_socket.
        async_send(boost::asio::buffer(_oarchive_stream.str()), 0,
        boost::bind(&Transmitter::onSend, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Transmitter::onSend(const boost::system::error_code& ec,
                         std::size_t bytes_transfered)
{
    if(!ec)
    {

    }
}