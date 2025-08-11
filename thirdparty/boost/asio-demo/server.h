#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Server
{
public:
    Server(net::io_context &io_context, unsigned short port);

private:
    void do_accept();

    tcp::acceptor acceptor_;
};