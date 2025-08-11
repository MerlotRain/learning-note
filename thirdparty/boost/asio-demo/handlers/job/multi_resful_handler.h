#pragma once

#include "../../api_handler.h"
#include "../../router.h"

class multi_resful_handler : public ApiHandler
{
public:
    void handle_request(
        const http::request<http::string_body> &req,
        http::response<http::string_body> &res, const std::unordered_map<std::string, std::string> &path_params = {}, const std::string &body_params = {}) override;

    http::verb get_method() const override
    {
        return http::verb::get;
    }

    std::string get_path() const override
    {
        return "/job/{jobid}/{taskname}";
    }
};
REGISTER_DYNAMIC_HANDLER(http::verb::get, "/job/{jobid}/{taskname}", multi_resful_handler);