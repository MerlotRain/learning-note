/*

{
    "code": 0,
    "msg": "success",
    "data": {
        "url": "https://gitee.com/",
        "name": "gitee"
    },
    "languages": [
        "C++",
        "Java",
        20
    ]
}

*/

/*

cJSON 这个库最大的问题是不能直接读文件，必须要先自己读文件进来然后给字符串解析，但是也简单，毕竟操作文本

*/

#include <cjson/cJSON.h>
#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    std::fstream file("./reply.json");
    if (file.is_open())
    {
        std::ostringstream ss;
        ss << file.rdbuf();

        std::string json = ss.str();

        cJSON *root = cJSON_Parse(json.c_str());
        std::cout << cJSON_GetObjectItem(root, "code")->valueint << std::endl;
        std::cout << cJSON_GetObjectItem(root, "msg")->valuestring << std::endl;
        cJSON *data = cJSON_GetObjectItem(root, "data");
        std::cout << cJSON_GetObjectItem(data, "url")->valuestring << std::endl;
        std::cout << cJSON_GetObjectItem(data, "name")->valuestring << std::endl;

        cJSON *language = cJSON_GetObjectItem(root, "languages");
        int size = cJSON_GetArraySize(language);
        for (int i = 0; i < size; ++i)
        {
            cJSON *child = cJSON_GetArrayItem(language, i);
            if (cJSON_IsString(child))
                std::cout << child->valuestring << std::endl;
            if (cJSON_IsNumber(child))
                std::cout << child->valueint << std::endl;
        }

        cJSON_Delete(root);
        file.close();
    }

    return 0;
}