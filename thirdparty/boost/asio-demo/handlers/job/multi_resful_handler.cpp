#include "multi_resful_handler.h"
#include <boost/json.hpp>
#include "static_vector.h"
#include <vector>

void multi_resful_handler::handle_request(
    const http::request<http::string_body> &req,
    http::response<http::string_body> &res,
    const std::unordered_map<std::string, std::string> &path_params, const std::string &body_params)
{

    auto jobid = path_params.at("jobid");
    auto taskname = path_params.at("taskname");

    res.result(http::status::not_found);
    res.set(http::field::content_type, "application/json");

    boost::json::object obj;
    obj["jobid"] = jobid;
    obj["taskname"] = taskname;

    res.body() = boost::json::serialize(obj);
    res.prepare_payload();
}