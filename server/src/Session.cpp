#include "Session.hpp"

Session::Session::Session(boost::asio::io_context& io_context, std::size_t id,
                          callbacks_t callbacks)
:   _io_context(io_context),
    _socket(io_context),
    _message("Hello from server\n"),
    _session_id(id),
    _callbacks(callbacks)
{
}
Session::~Session(){}

boost::asio::ip::tcp::socket& Session::socket()
{
    return _socket;
}

Session::session_ptr Session::create(boost::asio::io_context& io_context,
                                     std::size_t id, callbacks_t callbacks)
{
    return boost::shared_ptr<Session>(new Session(io_context, id, callbacks));
}

void Session::send(std::string&& msg)
{
    msg.append("\n");
    boost::asio::async_write(_socket, 
                    boost::asio::buffer(msg, msg.size()),
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
        std::string s = "[" + _username + "]: ";
        s.append((std::istreambuf_iterator<char>(&_buf)),
                         std::istreambuf_iterator<char>());
        _message_q.push(std::move(s));
        boost::asio::post(_io_context, boost::bind(_callbacks.broad_cast_func, _session_id));
        recv();
    }
    else
    {
        std::cout << "Connection closed - " << ec.message() << std::endl;
        _callbacks.remove_func(_session_id);
    }
}

void Session::authenticate()
{
    //read username
    boost::asio::async_read_until(_socket, _buf, '\n',
                        boost::bind(&Session::onUsername, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

void Session::onUsername(const boost::system::error_code& ec,
                     std::size_t bytes_received)
{
    // store username
    std::string s((std::istreambuf_iterator<char>(&_buf)),
                         std::istreambuf_iterator<char>());
    s.pop_back();
    _username = std::move(s);
    // read password
    boost::asio::async_read_until(_socket, _buf, '\n',
                        boost::bind(&Session::onPassword, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}
void Session::onPassword(const boost::system::error_code& ec,
                     std::size_t bytes_received)
{
    // store password
    std::string s((std::istreambuf_iterator<char>(&_buf)),
                         std::istreambuf_iterator<char>());
    s.pop_back();
    _password = std::move(s);

    // authenticate
    _callbacks.auth_func(this);
}