#pragma once

#include "../../router.h"
#include "../../api_handler.h"

class start_mapping_task_handler : public ApiHandler
{
public:
    void handle_request(
        const http::request<http::string_body> &req,
        http::response<http::string_body> &res, const std::unordered_map<std::string, std::string> &path_params = {}, const std::string &body_params = {}) override;

    http::verb get_method() const override;

    std::string get_path() const override;
};
REGISTER_API_HANDLER(start_mapping_task_handler);