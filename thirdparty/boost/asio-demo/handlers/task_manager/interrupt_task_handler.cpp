#include "interrupt_task_handler.h"
#include <task_manager.h>


/* ------------------------- interrupt_task_handler ------------------------- */

void interrupt_task_handler::handle_request(
        const http::request<http::string_body> &req, http::response<http::string_body> &res,
        const std::unordered_map<std::string, std::string> &path_params,
        const std::unordered_map<std::string, std::vector<std::string>> &query_params, const std::string &body_params)
{
}

http::verb interrupt_task_handler::get_method() const
{
    return http::verb::delete_;
}

std::string interrupt_task_handler::get_path() const
{
    return "/interruptTask/{taskId}";
}

/* ----------------------- interrupt_task_list_handler ---------------------- */

void interrupt_task_list_handler::handle_request(
        const http::request<http::string_body> &req, http::response<http::string_body> &res,
        const std::unordered_map<std::string, std::string> &path_params,
        const std::unordered_map<std::string, std::vector<std::string>> &query_params, const std::string &body_params)
{
}

http::verb interrupt_task_list_handler::get_method() const
{
    return http::verb::delete_;
}

std::string interrupt_task_list_handler::get_path() const
{
    return "/interruptTaskList";
}
