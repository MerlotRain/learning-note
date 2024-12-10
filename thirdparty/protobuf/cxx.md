# Protobuf 学习笔记

## 什么是 Protobuf？

Protocol Buffers（简称 Protobuf）是由 Google 开发的一种语言中立、平台无关的序列化数据格式。它通过定义 .proto 文件描述数据结构，然后生成高效的代码，用于数据的序列化和反序列化。相比 JSON 或 XML，Protobuf 更紧凑、性能更高。

## Protobuf 的主要特性

1. 高效性：

   • 紧凑的二进制格式，比 JSON 和 XML 更节省带宽和存储空间。
   
   • 解析速度快，适用于需要高性能的场景。
2. 跨语言、跨平台支持：

   • 支持多种语言：C++, Java, Python, Go, C#, JavaScript 等。

   • 可在不同系统间（如 Windows、Linux）使用。

3. 版本兼容性：

   • 添加字段时向后兼容，字段的移除或修改也有规则保障兼容性。

## 基本使用流程

### 1. 定义 .proto 文件

使用`.proto`文件描述数据结构。例如：
```proto
syntax = "proto3";

message Person {
  int32 id = 1;           // 唯一标识
  string name = 2;        // 姓名
  string email = 3;       // 邮箱
}
```

• syntax = "proto3"：指定使用 Protobuf 的版本 3。

• message：定义一个数据结构。

• 字段规则：

	• 每个字段都有唯一的编号，用于序列化和反序列化（如 id = 1）。

	• 字段类型支持基本类型（int32, string 等）和嵌套类型。

### 2. 编译 .proto 文件

使用 protoc 编译器生成目标语言代码：

protoc --proto_path=src --cpp_out=out src/person.proto

支持的目标语言包括：

• --cpp_out：生成 C++ 代码。

• --java_out：生成 Java 代码。

• --python_out：生成 Python 代码。

### 3. 使用生成的代码
#### 创建CMakeLists.txt
```cmake

cmake_minimum_required(VERSION 3.14)
project(test_protobuf)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PROTOBUF REQUIRED protobuf)
#find_package(protobuf REQUIRED CONFIG)

add_executable(main main.cpp message.pb.cc message.pb.h)
target_link_libraries(main PRIVATE ${PROTOBUF_LIBRARIES} )
target_include_directories(main PUBLIC ${PROTOBUF_INCLUDE_DIRS})

message("Protobuf_VERSION=${PROTOBUF_VERSION}")
message("Protobuf_LIBRARIES=${PROTOBUF_LIBRARIES}")
message("Protobuf_INCLUDE_DIRS=${PROTOBUF_INCLUDE_DIRS}")

```

以 C++ 为例，假设生成了 person.pb.h 和 person.pb.cc：

#### 序列化数据
```C++
#include "person.pb.h"
#include <fstream>

int main() {
    // 创建对象
    Person person;
    person.set_id(1);
    person.set_name("John Doe");
    person.set_email("john@example.com");

    // 序列化到文件
    std::ofstream output("person.bin", std::ios::binary);
    person.SerializeToOstream(&output);
    output.close();

    return 0;
}
```

#### 反序列化数据

```C++
#include "person.pb.h"
#include <fstream>
#include <iostream>

int main() {
    // 从文件反序列化
    Person person;
    std::ifstream input("person.bin", std::ios::binary);
    if (person.ParseFromIstream(&input)) {
        std::cout << "ID: " << person.id() << "\n";
        std::cout << "Name: " << person.name() << "\n";
        std::cout << "Email: " << person.email() << "\n";
    } else {
        std::cerr << "Failed to parse person.bin.\n";
    }

    return 0;
}
```

#### 高级功能

	1.	嵌套消息：
支持嵌套定义消息。

message Address {
  string city = 1;
  string country = 2;
}

message Person {
  string name = 1;
  Address address = 2; // 嵌套消息
}


	2.	枚举类型：

enum Status {
  UNKNOWN = 0;
  ACTIVE = 1;
  INACTIVE = 2;
}

message User {
  string name = 1;
  Status status = 2; // 使用枚举
}


	3.	重复字段：
可用于数组或列表。

message Group {
  repeated string members = 1; // 成员列表
}


	4.	版本兼容：
	•	新增字段：向后兼容。
	•	删除字段：标记为已弃用，不直接移除。
	•	字段编号不可重复。

Protobuf 与其他格式对比

特性	Protobuf	JSON	XML
数据格式	二进制	文本	文本
文件大小	小	中	大
解析速度	快	较慢	最慢
人类可读性	不可读	可读	可读
支持的类型	丰富	基本类型有限	丰富
版本兼容性	强	无	无

常见问题

	1.	如何保持字段编号的稳定性？
	•	在修改 .proto 文件时，不改变已有字段的编号，新增字段使用新的编号。
	2.	Protobuf 适合哪些场景？
	•	网络通信、日志存储、大规模数据序列化场景，如微服务间通信或跨语言数据传输。
	3.	如何调试 Protobuf 数据？
	•	使用 Protobuf 提供的 protoc 工具将二进制数据反序列化为可读格式：

protoc --decode_raw < binary_file

参考资源

	1.	Protobuf 官方文档
	2.	Google 开源项目
	3.	Protobuf 编程指南
