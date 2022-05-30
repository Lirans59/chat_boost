#include "Session.hpp"

Session::Session(boost::asio::ip::tcp::socket& socket,
                 readFunPtr onRead)
:   _socket(std::move(socket)),
    _message(std::move("This is Server\n")),
    _onRead(onRead)
{
}
Session::Session(boost::asio::io_context& io_contex,
                 readFunPtr onRead)
:   _socket(io_contex),
    _message(std::move("This is Server\n")),
    _onRead(onRead)
{
}


boost::shared_ptr<Session> Session::create(boost::asio::io_context& io_contex,
                                readFunPtr onRead)
{
    return boost::shared_ptr<Session>(new Session(io_contex, onRead));
}

void Session::write()
{
    std::cout << "sending message.." << std::endl;
    boost::asio::async_write(_socket, 
                    boost::asio::buffer(_message, _message.size()),
                    boost::bind(&Session::onWrite, this,
                                boost::asio::placeholders::error));
}

void Session::onWrite(const boost::system::error_code& ec)
{
    std::cout << "message sent" << std::endl;
}

void Session::read()
{
    std::cout << "Reading.." << std::endl;
    boost::asio::async_read(_socket, _buffer,
        std::bind(_onRead, std::placeholders::_1,
                           std::placeholders::_2,
                           this));
}
// void Session::onRead(const boost::system::error_code& ec,
//                      std::size_t bytes_received)
// {
//     if(!ec)
//     {
//         std::cout << bytes_received << "bytes received" << std::endl;
//     }
//     else
//     {
//         std::cout << "Connection closed" << std::endl;
//         _session_manager.removeSession(boost::shared_ptr<Session>(this));
//     }
// }

boost::asio::ip::tcp::socket& Session::getSocket()
{
    return _socket;
}

Session::~Session()
{

}