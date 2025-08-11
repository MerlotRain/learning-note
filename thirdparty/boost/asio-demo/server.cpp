#include "server.h"
#include "session.h"

Server::Server(net::io_context &io_context, unsigned short port)
    : acceptor_(io_context, {tcp::v4(), port})
{
    do_accept();
}

void Server::do_accept()
{
    acceptor_.async_accept([this](beast::error_code ec, tcp::socket socket) {
        if (!ec)
        {
            std::make_shared<Session>(std::move(socket))->start();
        }

        do_accept();
    });
}