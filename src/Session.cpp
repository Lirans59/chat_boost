#include "Session.hpp"

Session::Session::Session(boost::asio::io_context& io_context, unsigned int id,
                          Session::remove_ptr ptr)
:   _io_context(io_context),
    _socket(io_context),
    _message("Hello from server\n"),
    _session_id(id),
    _removeSession(ptr)
{
}
Session::~Session(){}

boost::asio::ip::tcp::socket& Session::socket()
{
    return _socket;
}

Session::session_ptr Session::create(boost::asio::io_context& io_context,
                                     unsigned int id, remove_ptr ptr)
{
    return boost::shared_ptr<Session>(new Session(io_context, id, ptr));
}

void Session::send()
{
    boost::asio::async_write(_socket, 
                    boost::asio::buffer(_message, _message.size()),
                    boost::bind(&Session::onSend, this,
                                boost::asio::placeholders::error));
}

void Session::onSend(const boost::system::error_code& ec)
{
    if(!ec)
    {
        std::cout << "message sent" << std::endl;
    }
    else
    {
        std::cout << "ERROR - send" << std::endl;
    }
}

void Session::recv()
{
    std::cout << "Reading.." << std::endl;
    _socket.async_receive(boost::asio::buffer(_message, MESSAGE_SIZE), 0,
                          boost::bind(&Session::onRecv, this,
                          boost::asio::placeholders::error,
                          boost::asio::placeholders::bytes_transferred));
}
void Session::onRecv(const boost::system::error_code& ec,
                     std::size_t bytes_received)
{
    if(!ec)
    {
        std::cout << bytes_received << "bytes received" << std::endl;
        recv();
    }
    else
    {
        std::cout << "Connection closed" << std::endl;
        _removeSession(_session_id);
    }
}