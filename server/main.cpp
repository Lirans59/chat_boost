#include <iostream>
#include <boost/asio.hpp>
#include "Server.hpp"

int main()
{
    boost::asio::io_context context;
    Server& myServer = Server::get(context);
    std::cout << "Server started.." << std::endl;
    context.run();
    return 0;
}