#include <curl/curl.h>
#include <cjson/cJSON.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

size_t read_callback(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t retcode;

    if (!stream)
    {
        /* 没有文件流，返回0表示结束 */
        return 0;
    }

    retcode = fread(ptr, size, nmemb, stream);
    if (retcode < nmemb)
    {
        /* 如果读取的字节数少于请求的字节数，可能是文件结束或错误 */
        if (feof(stream))
        {
            /* 文件结束，返回读取的字节数 */
            return retcode;
        }
        /* 读取错误，返回CURLE_READ_ERROR */
        return CURLE_READ_ERROR;
    }

    return retcode;
}

// 测试curl基本的method，包括GET,POST等

void test_curl_get_method(const std::string &url, std::map<std::string, std::string> &params)
{
    CURL *curl;
    CURLcode res;

    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        std::string full_url = url + "?";
        for (auto it = params.begin(); it != params.end(); ++it)
        {
            // key=value&...的形式
        }

        curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << curl_easy_strerror(res) << std::endl;
        }
    }
}

std::string test_curl_post_method(const std::string &url, const std::string &post_fields)
{
    // 我们知道，在http协议中，GET通常是不设置body参数的
    // post中，有些时候也不需要，我们直接将请求参数拼接到url中，带来的问题就是一些信息可能暴露出来，所以需要加密的信息我们都放在body参数中实现
    // 这些参数的组织形式有很多中，比如josn，txt等，具体是什么我们不去说，这里只说一下cURL怎么处理

    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        struct curl_slist *headers = NULL;

        // 如果需要设置Content-Type，可以在这里添加
        // 例如，对于JSON数据，你可以这样设置：
        // headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // 设置POST请求的主体内容
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        // http请求头的设置，这些内容怎么设置，一般和服务的提供方确认，我们只需要知道怎么写就行，不用太过关心
        if (headers)
        {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // 执行请求
        res = curl_easy_perform(curl);

        // 检查是否成功
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // 清理
        curl_easy_cleanup(curl);
        if (headers)
        {
            curl_slist_free_all(headers);
        }
    }
    curl_global_cleanup();

    return readBuffer;
}

int test_curl_put_method()
{
    CURL *curl;
    CURLcode res;
    FILE *hd_src;
    const char *url = "http://example.com/upload";
    const char *uploadfile = "path/to/your/file";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        /* 打开要上传的文件 */
        hd_src = fopen(uploadfile, "rb");
        if (!hd_src)
        {
            printf("无法打开文件\n");
            curl_easy_cleanup(curl);
            return -1;
        }

        /* 设置URL */
        curl_easy_setopt(curl, CURLOPT_URL, url);

        /* 设置PUT请求方法 */
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

        /* 设置读取数据的回调函数 */
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

        /* 设置读取数据的用户数据指针，这里为文件指针 */
        curl_easy_setopt(curl, CURLOPT_READDATA, (void *)hd_src);

        /* 设置上传文件的大小 */
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)-1);

        /* 执行请求 */
        res = curl_easy_perform(curl);

        /* 检查错误 */
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            printf("文件上传成功\n");
        }

        /* 关闭文件 */
        fclose(hd_src);

        /* 清理libcurl资源 */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
