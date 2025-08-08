#pragma once

#include "api_handler.h"
#include <map>
#include <memory>
#include <vector>
#include <boost/beast/http.hpp>

namespace http = boost::beast::http;

class Router
{
public:
    static void register_handler(ApiHandlerPtr handler);

    static ApiHandler *route(http::verb method, const std::string &path);

    static std::vector<std::pair<std::string, std::string>> get_routes();

private:
    using HandleMapping = std::map<std::pair<http::verb, std::string>, ApiHandlerPtr>;
    static HandleMapping &get_handlers();
};

#define REGISTER_API_HANDLER(HandlerClass)                                  \
    namespace                                                               \
    {                                                                       \
        struct HandlerClass##Register                                       \
        {                                                                   \
            HandlerClass##Register()                                        \
            {                                                               \
                Router::register_handler(std::make_unique<HandlerClass>()); \
            }                                                               \
        } HandlerClass##_register;                                          \
    }