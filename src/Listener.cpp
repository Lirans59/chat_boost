#include "Listener.hpp"
#include "Session.hpp"

Listener::Listener(boost::asio::io_context& io_context,
                   SessionManager& session_manager,
                   acceptFunPtr func)
:   _io_context(io_context),
    _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT)),
    _onAccept(func)
{
    std::cout << "Listener Ctor" << std::endl;
    doAccept();
}

void Listener::doAccept()
{
    auto new_session_ptr = Session::create(_io_context, _session_manager);
    _acceptor.async_accept(new_session_ptr->getSocket(),
        std::bind(_onAccept, std::placeholders::_1, new_session_ptr));
}

Listener::~Listener()
{

} 