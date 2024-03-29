#include "Session.hpp"

Session::Session::Session(boost::asio::io_context& io_context, std::size_t id,
                          Session::remove_func remove_func,
                          Session::broad_cast_func broad_cast_func)
:   _io_context(io_context),
    _socket(io_context),
    _message("Hello from server\n"),
    _session_id(id),
    _removeSession(remove_func),
    _broad_cast(broad_cast_func)
{
}
Session::~Session(){}

boost::asio::ip::tcp::socket& Session::socket()
{
    return _socket;
}

Session::session_ptr Session::create(boost::asio::io_context& io_context,
                                     std::size_t id, remove_func remove_func,
                                     broad_cast_func broad_cast_func)
{
    return boost::shared_ptr<Session>(new Session(io_context, id, remove_func, broad_cast_func));
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
        
    }
    else
    {
        std::cout << "ERROR - send" << std::endl;
    }
}

void Session::recv()
{
    boost::asio::async_read_until(_socket, _buf, '\n',
                        boost::bind(&Session::onRecv, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}
void Session::onRecv(const boost::system::error_code& ec,
                     std::size_t bytes_received)
{
    if(!ec)
    {
        //push message to message queue and post
        std::string s((std::istreambuf_iterator<char>(&_buf)),
                         std::istreambuf_iterator<char>());
        _message_q.push(std::move(s));
        boost::asio::post(_io_context, boost::bind(_broad_cast, _session_id));
        recv();
    }
    else
    {
        std::cout << "Connection closed - " << ec.message() << std::endl;
        _removeSession(_session_id);
    }
}