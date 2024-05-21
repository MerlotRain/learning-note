# YAML

## 介绍

YAML 作为系统级别的配置非常好用，之前使用过`XML`作为软件系统配置，总体感觉有两个问题

* 臃肿 XML的特性决定的，配置后非常大，会有很多其实没什么用的行

* 可读性差 因为臃肿，所以读起来很不方便，当需要修改的时候很痛苦，而且读`XML`的时候也很繁琐，无论是`tinyxml2`,`libxml2`,`qdom`,`qxmlstream`，用起来都有很多不舒服的点

## YAML基本格式

```yaml

server:  
  hostname: localhost  
  port: 8080  
  paths:  
    root: /var/www  
    logs: /var/log/myapp  
database:  
  username: myuser  
  password: mypassword

numbers:
  - 1.0
  - 2.0
  - 3.0

numbers2: [1,2,3,4]

```

整体看下来很`Json`类似，也比较好理解

## 解析

```c++

#include <yaml-cpp/yaml.h>  
#include <iostream>  
#include <string>  
  
int main() {  
    YAML::Node config = YAML::LoadFile("config.yaml");  
  
    // 检查 'server' 键是否存在，并且它是一个映射（mapping）  
    if (config["server"] && config["server"].IsMap()) {  
        // 获取 'server' 映射  
        const YAML::Node& server = config["server"];  
  
        // 访问 'server' 映射中的键值对  
        std::string hostname = server["hostname"].as<std::string>();  
        int port = server["port"].as<int>();  
  
        std::cout << "Hostname: " << hostname << std::endl;  
        std::cout << "Port: " << port << std::endl;  
  
        // 解析 'paths' 子映射  
        if (server["paths"] && server["paths"].IsMap()) {  
            const YAML::Node& paths = server["paths"];  
            std::string rootPath = paths["root"].as<std::string>();  
            std::string logsPath = paths["logs"].as<std::string>();  
  
            std::cout << "Root path: " << rootPath << std::endl;  
            std::cout << "Logs path: " << logsPath << std::endl;  
        }  
    }  
  
    // 检查 'database' 键是否存在，并且它是一个映射（mapping）  
    if (config["database"] && config["database"].IsMap()) {  
        // 获取 'database' 映射  
        const YAML::Node& database = config["database"];  
  
        // 访问 'database' 映射中的键值对  
        std::string username = database["username"].as<std::string>();  
        std::string password = database["password"].as<std::string>();  
  
        std::cout << "Database username: " << username << std::endl;  
        std::cout << "Database password: " << password << std::endl;  
    }  


    // 检查 'numbers' 键是否存在，并且它是一个序列（列表）  
    if (config["numbers"] && config["numbers"].IsSequence()) {  
        // 尝试将序列转换为 std::vector<double>  
        try {  
            std::vector<double> numbers = config["numbers"].as<std::vector<double>>();  
  
            // 遍历并打印 vector 中的元素  
            for (const auto& num : numbers) {  
                std::cout << num << std::endl;  
            }  
        } catch (YAML::BadConversion& e) {  
            // 如果转换失败，捕获异常并处理  
            std::cerr << "Failed to convert 'numbers' to std::vector<double>: " << e.what() << std::endl;  
        }  
    } else {  
        std::cerr << "'numbers' key not found or is not a sequence." << std::endl;  
    } 
  
    return 0;  
}

```

## 生成

```c++

#include <fstream>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <assert.h>

int main()
{
  YAML::Node node;
  assert(node.IsNull());
  node["key"] = "value";
  if (node["mascot"])
    std::cout << node["mascot"].as<std::string>() << "\n";

  node["number"] = 255;
  assert(node.IsMap());
  node["seq"].push_back("first element");
  node["seq"].push_back("second element");

  YAML::Node node_2;
  node_2.push_back("first item");
  node_2.push_back("second_item");
  node_2.push_back("third_item");
  std::vector<int> v = {1, 3, 5, 7, 9};
  node_2.push_back(v);
  assert(node_2.IsSequence());

  assert(node_2[0].as<std::string>() == "first item");
  auto it = node_2.begin();
  for (; it != node_2.end(); it++)
    std::cout << *(it) << std::endl;

  node_2["key"] = "value";
  assert(node_2.IsMap());
  assert(node_2[0].as<std::string>() == "first item");
  node["node_2"] = node_2;
  node["pointer_to_first_element"] = node["seq"][0];
  assert(node["pointer_to_first_element"].as<std::string>() == "first element");

  node.remove(node["seq"][0]);
  node.remove("pointer_to_first_element");

  std::ofstream outfile("output.yaml");
  if (!outfile.good())
  {
    std::cerr << "Failed to open file for writing." << std::endl;
    return 1;
  }

  outfile << node;
  outfile.close();
}

```
