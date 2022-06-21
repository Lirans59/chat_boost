#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context)
:   _io_contex(io_context),
    _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT)),
    _session_count(0),
    _db_users("users.db3")
{
    _callbacks.remove_func = boost::bind(&Server::doRemoveSession, this, boost::placeholders::_1);
    _callbacks.broad_cast_func = boost::bind(&Server::doBroadCast, this, boost::placeholders::_1);
    _callbacks.auth_func = boost::bind(&Server::doAuthentication, this, boost::placeholders::_1);
    doAccept();
}
Server::~Server(){}

Server& Server::get(boost::asio::io_context& io_context)
{
    static Server instance(io_context);
    return instance;
}

void Server::doAccept()
{
    auto new_session = Session::create(_io_contex, _session_count, _callbacks);
    _acceptor.async_accept(new_session->socket(),
        boost::bind(&Server::onAccept, this,
                    boost::asio::placeholders::error,
                    new_session));
}

void Server::onAccept(const boost::system::error_code& ec,
                      Session::session_ptr session)
{
    if(!ec)
    {
        std::cout << "New connection" << std::endl;
        boost::asio::ip::tcp::endpoint remote_ep = session->socket().remote_endpoint();
        std::cout << remote_ep.address() << " : " << remote_ep.port() << std::endl;
        
        _session_pool.emplace(_session_count, session);
        _session_count++;
        session->send(std::string("yes this is dog"));
        session->authenticate();
    }
    else
    {
        std::cout << "ERROR - accept" << std::endl;
    }
    doAccept();
}

void Server::doRemoveSession(std::size_t id)
{
    _session_pool.erase(id);
}

void Server::doBroadCast(std::size_t id)
{
    std::string temp(std::move(_session_pool[id]->_message_q.back()));
    _session_pool[id]->_message_q.pop();
    for(auto it : _session_pool)
    {
        if(it.first != id){
            boost::asio::async_write(it.second->socket(),
                boost::asio::buffer(temp, temp.size()),
                boost::bind(&Server::onSend, this,
                boost::asio::placeholders::error, id));
        }
    }
}
void Server::onSend(const boost::system::error_code& ec, std::size_t id)
{
    if(!ec)
    {
    }
}

void Server::doAuthentication(Session *session)
{
    if(_db_users.valid(session->_username, session->_password))
    {
        session->_password.clear();
        session->send(std::string("\nWelcome ") + session->_username + "!\n");
        session->recv();
    }
    else
    {
        session->send(std::string("Wrong username/password"));
        doRemoveSession(session->_session_id);
    }
}