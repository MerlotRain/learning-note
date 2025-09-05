#include "query_task_detail_handler.h"
#include <boost/json.hpp>

/* ------------------------ query_task_detail_handler ----------------------- */

void query_task_detail_handler::handle_request(
        const http::request<http::string_body> &req, http::response<http::string_body> &res,
        const std::unordered_map<std::string, std::string> &path_params,
        const std::unordered_map<std::string, std::vector<std::string>> &query_params, const std::string &body_params)
{
    res.result(http::status::ok);
    res.set(http::field::content_type, "application/json");

    boost::json::object obj;

    res.body() = boost::json::serialize(obj);
    res.prepare_payload();
}

http::verb query_task_detail_handler::get_method() const
{
    return http::verb::get;
}

std::string query_task_detail_handler::get_path() const
{
    return "/taskDetail/{taskId}";
}

/* --------------------- query_task_detail_list_handler --------------------- */

void query_task_detail_list_handler::handle_request(
        const http::request<http::string_body> &req, http::response<http::string_body> &res,
        const std::unordered_map<std::string, std::string> &path_params,
        const std::unordered_map<std::string, std::vector<std::string>> &query_params, const std::string &body_params)
{
    res.result(http::status::ok);
    res.set(http::field::content_type, "application/json");

    boost::json::object obj;
    res.body() = boost::json::serialize(obj);
    res.prepare_payload();
}

http::verb query_task_detail_list_handler::get_method() const
{
    return http::verb::get;
}

std::string query_task_detail_list_handler::get_path() const
{
    return "/taskDetailList";
}