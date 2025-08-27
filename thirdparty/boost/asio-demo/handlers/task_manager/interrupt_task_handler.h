#pragma once

#include <router.h>
#include <session.h>

class interrupt_task_handler : public ApiHandler
{
public:
    void handle_request(const http::request<http::string_body> &req, http::response<http::string_body> &res,
                        const std::unordered_map<std::string, std::string> &path_params = {},
                        const std::unordered_map<std::string, std::vector<std::string>> &query_params = {},
                        const std::string &body_params = {}) override;

    http::verb get_method() const override;

    std::string get_path() const override;
};
REGISTER_DYNAMIC_HANDLER(http::verb::get, "/interruptTask/{taskId}", interrupt_task_handler)

class interrupt_task_list_handler : public ApiHandler
{
public:
    void handle_request(const http::request<http::string_body> &req, http::response<http::string_body> &res,
                        const std::unordered_map<std::string, std::string> &path_params = {},
                        const std::unordered_map<std::string, std::vector<std::string>> &query_params = {},
                        const std::string &body_params = {}) override;
                        
    http::verb get_method() const override;
    std::string get_path() const override;
};
REGISTER_STATIC_HANDLER(interrupt_task_list_handler)