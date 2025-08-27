#pragma once

#include <boost/beast/http.hpp>
#include <router_export.h>

namespace http = boost::beast::http;

class ROUTER_EXPORT ApiHandler
{
public:
    virtual ~ApiHandler() = default;
    virtual void handle_request(const http::request<http::string_body> &req, http::response<http::string_body> &res,
                                const std::unordered_map<std::string, std::string> &path_params = {},
                                const std::unordered_map<std::string, std::vector<std::string>> &query_params = {},
                                const std::string &body_params = {}) = 0;
    virtual http::verb get_method() const = 0;
    virtual std::string get_path() const = 0;

protected:
    std::string get_first(const std::unordered_map<std::string, std::vector<std::string>> &params,
                          const std::string &key)
    {
        auto it = params.find(key);
        if (it != params.end() && !it->second.empty())
            return it->second.front();
        return {};
    }

    std::vector<std::string> get_all(const std::unordered_map<std::string, std::vector<std::string>> &params,
                                     const std::string &key)
    {
        auto it = params.find(key);
        if (it != params.end())
            return it->second;
        return {};
    }

    bool has_key(const std::unordered_map<std::string, std::vector<std::string>> &params, const std::string &key)
    {
        return params.find(key) != params.end();
    }
};
using ApiHandlerPtr = std::shared_ptr<ApiHandler>;