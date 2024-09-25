#ifdef _MSC_VER
#define SERVER_CORE_API __declspec(dllexport)
#else
#define SERVER_CORE_API __attribute__((visibility("default")))
#endif

#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>

#include <cjson/cJSON.h>
#include <curl/curl.h>

/* ---------------------------- export functions ---------------------------- */

extern "C" SERVER_CORE_API bool queryDomainName(std::string &domain,
                                                int location);

/* ---------------------------- static functions ---------------------------- */

static std::optional<std::string> query_mac_address();

static std::string request_domain();

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp);

/* ------------------------- function implementation ------------------------ */

#ifdef _WIN32
#include <iphlpapi.h>
#include <stdio.h>
#include <winsock2.h>

std::optional<std::string> query_mac_address() {
  std::stringstream ss;
  PIP_ADAPTER_INFO pAdapterInfo;
  ULONG ulOutBufLen = sizeof(pAdapterInfo);
  pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));

  if (pAdapterInfo == NULL) {
    printf("Error allocating memory\n");
    return std::nullopt;
  }

  if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
    free(pAdapterInfo);
    pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);

    if (pAdapterInfo == NULL) {
      printf("Error allocating memory\n");
      return std::nullopt;
    }
  }

  if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR) {
    for (PIP_ADAPTER_INFO pCurrentAdapter = pAdapterInfo; pCurrentAdapter;
         pCurrentAdapter = pCurrentAdapter->Next) {
      printf("Adapter Name: %s\n", pCurrentAdapter->AdapterName);
      for (UINT i = 0; i < pCurrentAdapter->AddressLength; i++) {
        i == (pCurrentAdapter->AddressLength - 1)
            ? ss << std::hex << std::setw(2) << std::setfill('0')
                 << (int)pCurrentAdapter->Address[i]
            : ss << std::hex << std::setw(2) << std::setfill('0')
                 << (int)pCurrentAdapter->Address[i] << ":";
      }
      break;
    }
  } else {
    printf("GetAdaptersInfo failed with error: %d\n", GetLastError());
  }

  if (pAdapterInfo) {
    free(pAdapterInfo);
  }

  return ss.str();
}

#else

std::optional<std::string> query_mac_address() {}

#endif

static int reply_code;
static std::string reply_url;

std::string request_domain(int location) {

  auto mac_res = query_mac_address();
  std::string macAddress = mac_res.has_value() ? mac_res.value() : "0";
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  std::string url;
  switch (location) {
  case 0:
    url = std::string("https:/tsc-:12006")
              .append("/")
              .append(macAddress)
              .append("/yx");
    break;
  case 1:
    url = std::string("https:/tsc-:12006")
              .append("/")
              .append(macAddress)
              .append("/yx");
    break;
  case 2:
    url = std::string("https:/tsc-:12006")
              .append("/")
              .append(macAddress)
              .append("/yx");
    break;
  default:
    url = std::string("https:/tsc-:12006")
              .append("/")
              .append(macAddress)
              .append("/yx");
    break;
  }
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // 设置请求头
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    } else {
      cJSON *root = cJSON_Parse(readBuffer.c_str());
      if (!root) {
        fprintf(stderr, "Error before: [%s]\n", cJSON_GetErrorPtr());
      } else {
        cJSON *code = cJSON_GetObjectItem(root, "code");
        cJSON *data = cJSON_GetObjectItem(root, "data");
        if (!code || !data) {
          fprintf(stderr, "Error before: [%s]\n", cJSON_GetErrorPtr());
          return std::string();
        }

        if (cJSON_IsNumber(code))
          reply_code = code->valueint;

        if (cJSON_IsObject(data)) {
          reply_url = cJSON_GetObjectItem(data, "url")->string;
        }

        cJSON_Delete(root);
      }
    }

    curl_easy_cleanup(curl);
  }

  return std::string();
}

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

extern "C" SERVER_CORE_API bool queryDomainName(std::string &domain,
                                                int location) {}