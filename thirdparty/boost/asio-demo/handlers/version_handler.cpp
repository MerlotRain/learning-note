#include "version_handler.h"
#include <boost/json.hpp>
#include <share_version.h>

void version_handler::handle_request(const http::request<http::string_body> &req,
                                     http::response<http::string_body> &res,
                                     const std::unordered_map<std::string, std::string> &path_params,
                                     const std::unordered_map<std::string, std::vector<std::string>> &query_params,
                                     const std::string &body_params)
{
    res.result(http::status::ok);
    res.set(http::field::content_type, "application/json");

    boost::json::object obj;
    obj["code"] = 0;
    obj["message"] = "success";
    obj["version"] = SAE_VERSION_STRING;

    res.body() = boost::json::serialize(obj);
    res.prepare_payload();
}

http::verb version_handler::get_method() const
{
    return http::verb::get;
}

std::string version_handler::get_path() const
{
    return "/version";
}