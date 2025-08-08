#include <iostream>
#include <string>
#include <memory>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind/bind.hpp>
#include <ctime>

#include "router.h"
#include "api_handler.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
using namespace std;

class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start()
    {
        read_request();
    }

private:
    void read_request()
    {
        req_ = {};

        http::async_read(socket_, buffer_, req_,
                         beast::bind_front_handler(
                             &Session::handle_read,
                             shared_from_this()));
    }

    void handle_read(beast::error_code ec, size_t bytes_transferred)
    {
        if (ec == http::error::end_of_stream)
        {
            socket_.shutdown(tcp::socket::shutdown_send, ec);
            return;
        }
        if (ec)
        {
            std::cerr << "Read error: " << ec.message() << std::endl;
            return;
        }

        process_request();
    }

    void process_request()
    {
        res_.version(req_.version());
        res_.keep_alive(req_.keep_alive());

        auto *handler = Router::route(req_.method(), req_.target());

        if (handler)
        {
            handler->handle_request(req_, res_);
        }
        else
        {
            if (req_.method() != http::verb::get &&
                req_.method() != http::verb::head)
            {
                handle_bad_request();
            }
            else
            {
                handle_not_found();
            }
        }

        write_response();
    }

    void handle_not_found()
    {
        res_.result(http::status::not_found);
        res_.set(http::field::content_type, "text/html");
        res_.body() =
            "<html>"
            "<head><title>Not Found</title></head>"
            "<body><h1>404 Not Found</h1></body>"
            "</html>";
        res_.prepare_payload();
    }

    void handle_bad_request()
    {
        res_.result(http::status::bad_request);
        res_.set(http::field::content_type, "text/html");
        res_.body() =
            "<html>"
            "<head><title>Bad Request</title></head>"
            "<body><h1>400 Bad Request</h1></body>"
            "</html>";
        res_.prepare_payload();
    }

    void write_response()
    {
        auto self = shared_from_this();

        http::async_write(socket_, res_,
                          [self](beast::error_code ec, size_t)
                          {
                              if (ec)
                              {
                                  std::cerr << "Write error: " << ec.message() << std::endl;
                                  return;
                              }

                              if (self->res_.keep_alive())
                              {
                                  self->read_request();
                              }
                              else
                              {
                                  self->socket_.shutdown(tcp::socket::shutdown_send, ec);
                              }
                          });
    }

    tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
    http::response<http::string_body> res_;
};

class Server
{
public:
    Server(net::io_context &io_context, unsigned short port)
        : acceptor_(io_context, {tcp::v4(), port})
    {
        do_accept();
    }

private:
    void do_accept()
    {
        acceptor_.async_accept(
            [this](beast::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    std::make_shared<Session>(std::move(socket))->start();
                }

                do_accept();
            });
    }

    tcp::acceptor acceptor_;
};

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <port>\n";
            return 1;
        }

        auto const port = static_cast<unsigned short>(std::atoi(argv[1]));

        net::io_context io_context;

        Server server(io_context, port);
        std::cout << "HTTP server started on port " << port << std::endl;

        io_context.run();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}