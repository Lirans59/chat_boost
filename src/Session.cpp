#include "Session.hpp"

Session::Session::Session(boost::asio::io_context& io_context, std::size_t id,
                          Session::remove_ptr ptr)
:   _io_context(io_context),
    _socket(io_context),
    _message("Hello from server\n"),
    _session_id(id),
    _removeSession(ptr),
    _Tx(this)
{
    printf("Session Ctor\n");
}
Session::~Session(){}

boost::asio::ip::tcp::socket& Session::socket()
{
    return _socket;
}

Session::session_ptr Session::create(boost::asio::io_context& io_context,
                                     std::size_t id, remove_ptr ptr)
{
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa\n");
    return boost::shared_ptr<Session>(new Session(io_context, id, ptr));
}

void Session::send()
{
    // boost::asio::async_write(_socket, 
    //                 boost::asio::buffer(_message, _message.size()),
    //                 boost::bind(&Session::onSend, this,
    //                             boost::asio::placeholders::error));
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
    _socket.async_receive(boost::asio::buffer(_message, MESSAGE_SIZE), 0,//read header
                          boost::bind(&Session::onRecv, this,
                          boost::asio::placeholders::error,
                          boost::asio::placeholders::bytes_transferred));
}
void Session::onRecv(const boost::system::error_code& ec,
                     std::size_t bytes_received)
{
    if(!ec)
    {
        std::cout << bytes_received << "read successfully" << std::endl;
        recv();
    }
    else
    {
        std::cout << "Connection closed - " << ec.message() << std::endl;
        _removeSession(_session_id);
    }
}
// void Session::recvBody()
// {
//     _socket.async_receive(boost::asio::buffer(_message, MESSAGE_SIZE), 0, // read header
//                           boost::bind(&Session::onRecv, this,
//                           boost::asio::placeholders::error,
//                           boost::asio::placeholders::bytes_transferred));
//     std::cout << "message received: "  << _message << std::endl;
//     Session::recv();
// }