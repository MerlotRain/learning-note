#pragma once

#include "api_handler.h"
#include <boost/beast/http.hpp>
#include <map>
#include <memory>
#include <regex>
#include <vector>

namespace http = boost::beast::http;

class Router
{
public:
    static void register_static_handler(ApiHandlerPtr handler);
    static void register_dynamic_handler(http::verb method, const std::string &path, ApiHandlerPtr handler);
    static std::pair<ApiHandler *, std::unordered_map<std::string, std::string>> route(http::verb method,
                                                                                       const std::string &path);
    static std::vector<std::pair<std::string, std::string>> get_routes();

private:
    using StaticRoutes = std::map<std::pair<http::verb, std::string>, ApiHandlerPtr>;
    static StaticRoutes &get_static_routes();

    using DynamicRoute = std::tuple<std::regex, std::vector<std::string>, ApiHandlerPtr>;

    static std::vector<std::pair<http::verb, DynamicRoute>> &get_dynamic_routes();
};

#define REGISTER_STATIC_HANDLER(HandlerClass)                                  \
    namespace {                                                                \
    struct HandlerClass##Register                                              \
    {                                                                          \
        HandlerClass##Register()                                               \
        {                                                                      \
            Router::register_static_handler(std::make_shared<HandlerClass>()); \
        }                                                                      \
    } HandlerClass##_register;                                                 \
    }

#define REGISTER_DYNAMIC_HANDLER(Method, Path, HandlerClass)                                  \
    namespace {                                                                               \
    struct HandlerClass##Register                                                             \
    {                                                                                         \
        HandlerClass##Register()                                                              \
        {                                                                                     \
            Router::register_dynamic_handler(Method, Path, std::make_shared<HandlerClass>()); \
        }                                                                                     \
    } HandlerClass##_register;                                                                \
    }