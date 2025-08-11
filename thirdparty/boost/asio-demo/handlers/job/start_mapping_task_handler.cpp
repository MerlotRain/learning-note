#include "start_mapping_task_handler.h"
#include <boost/json.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "static_vector.h"

void start_mapping_task_handler::handle_request(const http::request<http::string_body> &req, 
    http::response<http::string_body> &res, const std::unordered_map<std::string, std::string> &path_params, const std::string &body)
{
    res.result(http::status::ok);
    res.set(http::field::content_type, "application/json");

    boost::uuids::random_generator gen;
    boost::uuids::uuid uuid = gen();

    std::string str_uuid = boost::uuids::to_string(uuid);
    static_vector::get_vector().push_back(str_uuid);

    boost::json::object obj;
    obj["message"] = "success";
    obj["jobid"] = str_uuid;

    res.body() = boost::json::serialize(obj);
    res.prepare_payload();
}

http::verb start_mapping_task_handler::get_method() const
{
    return http::verb::post;
}

std::string start_mapping_task_handler::get_path() const
{
    return "/job";
}