#pragma once

#include <boost/beast/http.hpp>

namespace http = boost::beast::http;

class ApiHandler
{
public:
    virtual ~ApiHandler() = default;
    virtual void handle_request(const http::request<http::string_body> &req,
                                http::response<http::string_body> &res, const std::unordered_map<std::string, std::string> &path_params = {}, const std::string &body_params = {}) = 0;
    virtual http::verb get_method() const = 0;
    virtual std::string get_path() const = 0;
};
using ApiHandlerPtr = std::shared_ptr<ApiHandler>;