#include "Listener.hpp"
#include "Session.hpp"

Listener::Listener(boost::asio::io_context& io_context,
                   SessionManager& session_manager)
:   _io_context(io_context),
    _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT)),
    _session_manager(session_manager)
{
    std::cout << "Listener Ctor" << std::endl;
    doAccept();
}

void Listener::doAccept()
{
    auto new_session_ptr = Session::create(_io_context, _session_manager);
    _acceptor.async_accept(new_session_ptr->getSocket(),
        boost::bind(&Listener::onAccept, this, boost::placeholders::_1, new_session_ptr));
}
void Listener::onAccept(const boost::system::error_code& ec,
                        boost::shared_ptr<Session> session_ptr)
{
    if(!ec)
    {
        std::cout << "New connection" << std::endl;
        _session_manager.addSession(session_ptr);
        session_ptr->write();
        session_ptr->read();
    }
    Listener::doAccept();
}

Listener::~Listener()
{

} 