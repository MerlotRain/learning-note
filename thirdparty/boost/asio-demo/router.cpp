#include "router.h"
#include <boost/algorithm/string.hpp>

void Router::register_static_handler(ApiHandlerPtr handler)
{
    auto key = std::make_pair(handler->get_method(), handler->get_path());
    get_static_routes().emplace(std::move(key), std::move(handler));
}

void Router::register_dynamic_handler(http::verb method, const std::string &path_template, ApiHandlerPtr handler)
{
    std::string regex_str = "^" + std::regex_replace(path_template, std::regex("\\{([^}]+)\\}"), "([^/]+)") + "$";

    std::vector<std::string> param_names;
    std::smatch matches;
    auto it = path_template.cbegin();
    while (std::regex_search(it, path_template.cend(), matches, std::regex("\\{([^}]+)\\}")))
    {
        param_names.push_back(matches[1].str());
        it = matches[0].second;
    }

    get_dynamic_routes().emplace_back(method, std::make_tuple(std::regex(regex_str), param_names, handler));
}

std::pair<ApiHandler *, std::unordered_map<std::string, std::string>> Router::route(http::verb method,
                                                                                    const std::string &path)
{
    if (auto it = get_static_routes().find({method, path}); it != get_static_routes().end())
    {
        return {it->second.get(), {}};
    }

    for (const auto &[route_method, dynamic_route]: get_dynamic_routes())
    {
        if (method != route_method)
            continue;

        const auto &[regex, param_names, handler] = dynamic_route;
        std::smatch matches;
        if (std::regex_match(path, matches, regex))
        {
            std::unordered_map<std::string, std::string> params;
            for (size_t i = 0; i < param_names.size(); ++i)
            {
                params[param_names[i]] = matches[i + 1].str();
            }
            return {handler.get(), params};
        }
    }

    return {nullptr, {}};
}

std::vector<std::pair<std::string, std::string>> Router::get_routes()
{
    std::vector<std::pair<std::string, std::string>> routes;
    for (const auto &[key, handler]: get_static_routes())
    {
        auto &&sv = boost::beast::http::to_string(key.first);
        std::string method = std::string(sv.begin(), sv.end());
        routes.emplace_back(method, key.second);
    }
    return routes;
}

Router::StaticRoutes &Router::get_static_routes()
{
    static StaticRoutes handlers;
    return handlers;
}

std::vector<std::pair<http::verb, Router::DynamicRoute>> &Router::get_dynamic_routes()
{
    static std::vector<std::pair<http::verb, Router::DynamicRoute>> routes;
    return routes;
}
