#include <iostream>
#include <boost/asio.hpp>
#include "Listener.hpp"
#include "Server.hpp"

int main()
{
    boost::asio::io_context context;
    Server server(context);
    server.start();
    std::cout << "yes" << std::endl;
    context.run();
    return 0;
}