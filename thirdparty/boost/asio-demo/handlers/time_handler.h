#pragma once
#include "../api_handler.h"
#include <ctime>
#include "../router.h"

class TimeHandler : public ApiHandler
{
public:
    void handle_request(
        const http::request<http::string_body> &req,
        http::response<http::string_body> &res, const std::unordered_map<std::string, std::string> &path_params = {}, const std::string &body_params = {}) override
    {

        res.result(http::status::ok);
        res.set(http::field::content_type, "text/plain");

        time_t now = time(nullptr);
        tm *local = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", local);
        res.body() = buffer;
        res.prepare_payload();
    }

    http::verb get_method() const override
    {
        return http::verb::get;
    }

    std::string get_path() const override
    {
        return "/time";
    }
};

REGISTER_API_HANDLER(TimeHandler);