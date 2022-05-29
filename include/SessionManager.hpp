#ifndef SESSIONMANAGER_HPP
#define SESSIONMANAGER_HPP

#pragma once

#include <iostream>
#include <list>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <Session.hpp>

#define MAX_CONNECTIONS 30

class Session;

class SessionManager : public boost::enable_shared_from_this<SessionManager>
{
public:
    SessionManager();
    ~SessionManager();
    void addSession(boost::shared_ptr<Session> session_ptr);
    void removeSession(boost::shared_ptr<Session> session_ptr);

private:
    std::list<boost::shared_ptr<Session>>   _sessions;
};

#endif // SESSIONMANAGER_HPP