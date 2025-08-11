#include "check_task_handler.h"
#include <boost/json.hpp>
#include "static_vector.h"
#include <vector>

void check_task_handler::handle_request(
    const http::request<http::string_body> &req,
    http::response<http::string_body> &res,
    const std::unordered_map<std::string, std::string> &path_params, const std::string &body_params)
{
    auto jobid = path_params.at("jobid");
    auto&& jobids =  static_vector::get_vector();
    auto it_find = std::find_if(jobids.begin(), jobids.end(), [jobid](const std::string &id) {
        return id == jobid;
    });

    if(it_find == jobids.end()) {
        res.result(http::status::not_found);
        res.set(http::field::content_type, "application/json");
        res.body() = R"({"error": "Job not found"})";
    }
    else
    {
        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");
        res.body() = R"({"message": "success", "status": "running"})";
    }
    res.prepare_payload();
}