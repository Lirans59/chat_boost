#include "Listener.hpp"
#include "Session.hpp"

Listener::Listener(boost::asio::io_context& io_context,
                   acceptFunPtr accept_func,
                   readFunPtr read_func)
:   _io_context(io_context),
    _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT)),
    _onAccept(accept_func), _onRead(read_func)
{
    std::cout << "Listener Ctor" << std::endl;
    doAccept();
}

void Listener::doAccept()
{
    auto new_session_ptr = Session::create(_io_context, _onRead);
    _acceptor.async_accept(new_session_ptr->getSocket(),
        std::bind(_onAccept, std::placeholders::_1, new_session_ptr));
}

Listener::~Listener()
{

} 