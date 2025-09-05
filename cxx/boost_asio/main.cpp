
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <gflags/gflags.h>
#include <iostream>
#include <session.h>

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Server
{
public:
    Server(net::io_context &io_context, unsigned short port) : acceptor_(io_context, {tcp::v4(), port})
    {
        do_accept();
    }

private:
    void do_accept()
    {
        acceptor_.async_accept([this](beast::error_code ec, tcp::socket socket) {
            if (!ec)
            {
                std::make_shared<Session>(std::move(socket))->start();
            }

            do_accept();
        });
    }

    tcp::acceptor acceptor_;
};

static void custom_terminate_handler()
{
    try
    {
        throw;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unhandled unknown exception!" << std::endl;
    }
    std::abort();
}

DEFINE_int32(port, 8080, "Server port number");
DEFINE_string(log_dir, "./logs", "Log directory path");

int main(int argc, char *argv[])
{
    std::set_terminate(custom_terminate_handler);
    gflags::SetUsageMessage("Usage: " + std::string(argv[0]) +
                            " --port=<port> --log_dir=<path>\n"
                            "Example:\n"
                            "  " +
                            std::string(argv[0]) + " --port=8080 --log_dir=./logs");

    try
    {
        gflags::ParseCommandLineFlags(&argc, &argv, true);
        if (FLAGS_port <= 0 || FLAGS_log_dir.empty())
        {
            std::cerr << "Error: --port and --log_dir are required.\n\n";
            std::cerr << gflags::ProgramUsage();
            return 1;
        }

        std::cout << "Server will start on port: " << FLAGS_port << std::endl;
        std::cout << "Log directory: " << FLAGS_log_dir << std::endl;

        net::io_context io_context;
        Server server(io_context, FLAGS_port);
        io_context.run();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}