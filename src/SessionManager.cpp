#include "SessionManager.hpp"

SessionManager::SessionManager()
{
}

SessionManager::~SessionManager(){}

void SessionManager::addSession(boost::shared_ptr<Session> session_ptr)
{
    std::cout << "New connection inserted" << std::endl;
    _sessions.insert(_sessions.end(), session_ptr);
}

void SessionManager::removeSession(boost::shared_ptr<Session> session_ptr)
{
    for(auto it = _sessions.begin(); it != _sessions.end(); it++)
    {
        if(session_ptr.get() == it->get())
        {
            std::cout << "Connection erased" << std::endl;
            _sessions.erase(it);
            break;
        }
    }
}