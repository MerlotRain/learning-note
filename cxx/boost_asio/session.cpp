#include "session.h"
#include "router.h"
#include <iostream>

static std::string url_decode(const std::string &str)
{
    std::string ret;
    ret.reserve(str.size());

    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] == '%')
        {
            if (i + 2 < str.size())
            {
                try
                {
                    int value = std::stoi(str.substr(i + 1, 2), nullptr, 16);
                    ret += static_cast<char>(value);
                    i += 2;
                }
                catch (const std::exception &)
                {
                    ret += '%';
                }
            }
            else
            {
                ret += '%';
            }
        }
        else if (str[i] == '+')
        {
            ret += ' ';
        }
        else
        {
            ret += str[i];
        }
    }

    return ret;
}


static std::unordered_map<std::string, std::vector<std::string>> parse_query(const std::string &query)
{
    std::unordered_map<std::string, std::vector<std::string>> result;
    std::istringstream iss(query);
    std::string pair;

    std::regex re_index(R"((\w+)(\[\d*\]|\[\])?)");

    while (std::getline(iss, pair, '&'))
    {
        if (pair.empty())
            continue;

        auto pos = pair.find('=');
        std::string key, value;
        if (pos != std::string::npos)
        {
            key = pair.substr(0, pos);
            value = pair.substr(pos + 1);
        }
        else
        {
            key = pair;
            value = "";
        }

        key = url_decode(key);
        value = url_decode(value);

        std::smatch m;
        if (std::regex_match(key, m, re_index))
        {
            key = m[1];
        }

        std::istringstream vs(value);
        std::string v;
        while (std::getline(vs, v, ','))
        {
            if (!v.empty())
                result[key].push_back(v);
        }
    }

    return result;
}

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

    std::string target = req_.target();
    std::string path = target;
    std::string query;
    if (auto pos = target.find('?'); pos != std::string::npos)
    {
        path = target.substr(0, pos);
        query = target.substr(pos + 1);
    }

    auto [handler, params] = Router::route(req_.method(), path);

    auto query_params = parse_query(query);

    if (handler)
    {
        handler->handle_request(req_, res_, params, query_params, body);
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
