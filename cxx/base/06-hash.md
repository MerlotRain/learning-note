# Hash

本文介绍C++哈希相关的内容，主要包括`std::hash`,`std::unordered_set`,`std::unordered_multiset`.

其他两个`std::unordered_map`,`std::unordered_multimap`不会过多介绍，因为在存储的核心点，他们与`set`系列是一样的

## 一、`std::hash`

`std::hash`用于计算一个值的hash，通常来说，对于c++基本数据类型，已经内置了hash计算方式，对于复杂对象，我们的处理如下

```c++

struct Node
{
    std::string name;
    int value;
};

namespace std
{
    template <>
    struct hash<Node>
    {
        size_t operator()(const Node &node)
        {
            size_t h1 = std::hash<std::string>()(node.name);
            size_t h2 = std::hash<int>()(node.value);
            return h1 ^ (h2 << 1);
        }
    };
} // namespace std 

```

## 二、`std::unordered_set`

与普通的`set`类似，只能出现一个相同的相同的元素。

因为`unordered_set`将数据放在桶里，所以需要提供一个如上的hash重载，获取hash值

```C++

#include <iostream>  
#include <unordered_set>  
#include <functional> // 包含 std::hash  
  
// 自定义结构体  
struct Person {  
    std::string name;  
    int age;  
  
    Person(const std::string& n, int a) : name(n), age(a) {}  
  
    // 重载操作符 == 用于比较两个Person对象是否相等  
    bool operator==(const Person& other) const {  
        return name == other.name && age == other.age;  
    }  
};  
  
// 自定义哈希函数  
struct PersonHash {  
    size_t operator()(const Person& p) const {  
        size_t h1 = std::hash<std::string>()(p.name);  
        size_t h2 = std::hash<int>()(p.age);  
        return h1 ^ (h2 << 1); // 简单的组合方法，可以根据需要改进  
    }  
};  
  
// 自定义相等性比较函数  
struct PersonEqual {  
    bool operator()(const Person& lhs, const Person& rhs) const {  
        return lhs.name == rhs.name && lhs.age == rhs.age;  
    }  
};  
  
int main() {  
    // 使用自定义哈希函数和相等性比较函数的unordered_set  
    std::unordered_set<Person, PersonHash, PersonEqual> people;  
  
    // 插入元素  
    people.insert(Person("Alice", 30));  
    people.insert(Person("Bob", 25));  
  
    // 检查元素是否存在  
    if (people.find(Person("Alice", 30)) != people.end()) {  
        std::cout << "Alice is in the set." << std::endl;  
    }  
  
    // 遍历集合  
    for (const auto& person : people) {  
        std::cout << person.name << ", " << person.age << std::endl;  
    }  
  
    return 0;  
}

```