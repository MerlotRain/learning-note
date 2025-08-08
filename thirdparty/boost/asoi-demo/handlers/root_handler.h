// root_handler.h
#pragma once
#include "../api_handler.h"
#include "../router.h"

class RootHandler : public ApiHandler
{
public:
    void handle_request(
        const http::request<http::string_body> &req,
        http::response<http::string_body> &res) override
    {

        res.result(http::status::ok);
        res.set(http::field::content_type, "text/html");

        auto routes = Router::get_routes();

        std::string body = "<html><head><title>HTTP Server</title></head><body>";
        body += "<h1>Welcome to the HTTP Server</h1><p>Available endpoints:</p><ul>";

        for (const auto &[method, path] : routes)
        {
            body += "<li>" + method + " <a href='" + path + "'>" + path + "</a></li>";
        }

        body += "</ul></body></html>";

        res.body() = body;
        res.prepare_payload();
    }

    http::verb get_method() const override
    {
        return http::verb::get;
    }

    std::string get_path() const override
    {
        return "/";
    }
};

REGISTER_API_HANDLER(RootHandler);