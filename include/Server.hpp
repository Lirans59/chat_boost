#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include <iostream>
#include "Listener.hpp"

class Server
{
public:
    Server(boost::asio::io_context& io_context);
    ~Server();
    void start();

private:
    Listener _listener;
    //sessionManager sm; TO BE IMPLEMENTED
};

#endif // SERVER_HPP