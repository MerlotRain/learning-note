#include "router.h"
#include <boost/algorithm/string.hpp>

void Router::register_handler(ApiHandlerPtr handler)
{
    auto key = std::make_pair(handler->get_method(), handler->get_path());
    get_handlers().emplace(std::move(key), std::move(handler));
}

ApiHandler *Router::route(http::verb method, const std::string &path)
{
    auto it = get_handlers().find(std::make_pair(method, path));
    if (it != get_handlers().end())
    {
        return it->second.get();
    }
    return nullptr;
}

std::vector<std::pair<std::string, std::string>> Router::get_routes()
{
    std::vector<std::pair<std::string, std::string>> routes;
    for (const auto &[key, handler] : get_handlers())
    {
        auto &&sv = boost::beast::http::to_string(key.first);
        std::string method = std::string(sv.begin(), sv.end());
        routes.emplace_back(method,
                            key.second);
    }
    return routes;
}

Router::HandleMapping &Router::get_handlers()
{
    static HandleMapping handlers;
    return handlers;
}