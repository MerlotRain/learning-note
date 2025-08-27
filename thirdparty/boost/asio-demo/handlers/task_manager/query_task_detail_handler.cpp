#include "query_task_detail_handler.h"
#include <boost/json.hpp>
#include <task_manager.h>

/* ------------------------ query_task_detail_handler ----------------------- */

void query_task_detail_handler::handle_request(
        const http::request<http::string_body> &req, http::response<http::string_body> &res,
        const std::unordered_map<std::string, std::string> &path_params,
        const std::unordered_map<std::string, std::vector<std::string>> &query_params, const std::string &body_params)
{
    res.result(http::status::ok);
    res.set(http::field::content_type, "application/json");

    boost::json::object obj;
    auto info = TaskManager::instance()->getTaskInfo(path_params.at("taskId").c_str());
    if (info.has_value())
    {
        obj["code"] = 0;
        obj["message"] = "";
        boost::json::object data;

        data["id"] = info.value().id.toStdString();
        data["status"]=(int) info.value().status;
        data["createTime"] = info.value().createTime;
        data["startTime"] = info.value().startTime;
        data["endTime"] = info.value().endTime;
        data["progressText"] = info.value().progressText.toStdString();
        data["progressValue"]= info.value().progressValue;
        data["result"] = info.value().result;
        obj["data"] = data;
    }
    else
    {
        obj["code"] = -1;
        obj["message"] = "Task not found";
    }

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