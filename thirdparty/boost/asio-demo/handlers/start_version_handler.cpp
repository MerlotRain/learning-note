#include "start_version_handler.h"
#include <boost/json.hpp>

#define SAE_VERSION_STRING "1.0.4.9"

void StartVersionHandler::handle_request(const http::request<http::string_body> &req, http::response<http::string_body> &res, const std::unordered_map<std::string, std::string> &path_params, const std::string &body_params)
{
    res.result(http::status::ok);
    res.set(http::field::content_type, "application/json");

    boost::json::object obj;
    obj["message"] = "success";
    obj["version"] = SAE_VERSION_STRING;

    res.body() = boost::json::serialize(obj);
    res.prepare_payload();
}

http::verb StartVersionHandler::get_method() const
{
    return http::verb::get;
}

std::string StartVersionHandler::get_path() const
{
    return "/start/version";
}