#include "Client.hpp"

Client::Client(boost::asio::io_context& io_context)
:   _io_context(io_context),
    _socket(io_context),
    _internal_flag(0)
{
    doConnect();
}
Client::~Client(){}

void Client::doRecv()
{
    boost::asio::async_read_until(_socket, _buf, '\n',
        boost::bind(&Client::onRecv, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}
void Client::onRecv(const boost::system::error_code& ec, std::size_t bytes_transfered)
{
    if(!ec)
    {
        std::string s((std::istreambuf_iterator<char>(&_buf)),
            std::istreambuf_iterator<char>());
        std::cout << s;
        doRecv();
    }
    else
    {
        std::cout << "Connection closed" << std::endl;
        exit(1);
    }
}

void Client::doConnect()
{
    _socket.async_connect(boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), PORT),
        boost::bind(&Client::onConnect, this, boost::asio::placeholders::error));
}
void Client::onConnect(const boost::system::error_code& ec)
{
    if(!ec)
    {
        std::cout << "Connected!" << std::endl;
        doRecv();
        std::thread(&Client::getInput, this).detach();
        boost::asio::post(_io_context, boost::bind(&Client::doSend, this));
    }
}

void Client::doSend()
{
    if(!_message_q.empty())
    {
        // std::cout << _message_q.back() << std::endl;
        boost::asio::async_write(_socket,
            boost::asio::buffer(_message_q.back(), _message_q.back().size()),
            boost::bind(&Client::onSend,this, boost::asio::placeholders::error));
    }
    boost::asio::post(_io_context, boost::bind(&Client::doSend, this));
}
void Client::onSend(const boost::system::error_code& ec)
{
    if(!ec)
    {
        _message_q.pop();
    }
}

void Client::getInput()
{
    while(true)
    {
        switch(_internal_flag)
        {
            case 0:
                std::cout << "Username: ";
                _internal_flag++;
                break;
            case 1:
                std::cout << "Password: ";
                _internal_flag++;
                break;
            default:
                break;
        }
        std::string input;
        std::getline(std::cin, input);
        input.append("\n");
        _message_q.push(std::move(input));
    }
}