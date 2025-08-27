#include "pointcloud_format_convert_handler.h"
#include <boost/json.hpp>
#include <task_manager.h>

void pointcloud_format_convert_handler::handle_request(
        const http::request<http::string_body> &req, http::response<http::string_body> &res,
        const std::unordered_map<std::string, std::string> &path_params,
        const std::unordered_map<std::string, std::vector<std::string>> &query_params, const std::string &body_params)
{
    res.result(http::status::ok);
    res.set(http::field::content_type, "application/json");

    boost::json::object obj;
    obj["message"] = "success";

    res.body() = boost::json::serialize(obj);
    res.prepare_payload();
}

http::verb pointcloud_format_convert_handler::get_method() const
{
    return http::verb::post;
}

std::string pointcloud_format_convert_handler::get_path() const
{
    return "/pointcloudFormatConvert";
}