#include "session.h"
#include <iostream>
#include "router.h"
#include <iostream>

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {}

void Session::start()
{
    read_request();
}

void Session::read_request()
{
    req_ = {};

    http::async_read(socket_, buffer_, req_, beast::bind_front_handler(&Session::handle_read, shared_from_this()));
}

void Session::handle_read(beast::error_code ec, size_t bytes_transferred)
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

void Session::process_request()
{
    res_.version(req_.version());
    res_.keep_alive(req_.keep_alive());
    std::string body = req_.body();

    auto [handler, params] = Router::route(req_.method(), req_.target());

    if (handler)
    {
        handler->handle_request(req_, res_, params, body);
    }
    else
    {
        if (req_.method() != http::verb::get && req_.method() != http::verb::head)
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

void Session::handle_not_found()
{
    res_.result(http::status::not_found);
    res_.set(http::field::content_type, "text/html");
    res_.body() = "<html>"
                  "<head><title>Not Found</title></head>"
                  "<body><h1>404 Not Found</h1></body>"
                  "</html>";
    res_.prepare_payload();
}

void Session::handle_bad_request()
{
    res_.result(http::status::bad_request);
    res_.set(http::field::content_type, "text/html");
    res_.body() = "<html>"
                  "<head><title>Bad Request</title></head>"
                  "<body><h1>400 Bad Request</h1></body>"
                  "</html>";
    res_.prepare_payload();
}

void Session::write_response()
{
    auto self = shared_from_this();

    http::async_write(socket_, res_, [self](beast::error_code ec, size_t) {
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
