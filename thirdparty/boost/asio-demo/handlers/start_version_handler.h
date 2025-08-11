#pragma once

#include "../api_handler.h"
#include "../router.h"

class StartVersionHandler : public ApiHandler
{
public:
    void handle_request(
        const http::request<http::string_body> &req,
        http::response<http::string_body> &res, const std::unordered_map<std::string, std::string> &path_params = {}, const std::string &body_params = {}) override;

    http::verb get_method() const override;

    std::string get_path() const override;
};
REGISTER_API_HANDLER(StartVersionHandler);
