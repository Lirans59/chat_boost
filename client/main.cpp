#include <boost/asio.hpp>
#include "Client.hpp"

int main()
{
    boost::asio::io_context io_context;
    Client client(io_context);
    io_context.run();
}