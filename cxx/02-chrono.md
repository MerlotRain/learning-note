## 获取系统时间，也就是当前时间

```c++
#include <iostream>  
#include <chrono>  
#include <ctime>  
#include <iomanip>  
  
int main() {  
    // 获取当前系统时间  
    auto now = std::chrono::system_clock::now();  
    // 转换为time_t  
    std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24)); // 举例：获取前一天的本地时间  
  
    // 转换为tm结构  
    std::tm* now_tm = std::localtime(&now_c);  
  
    // 输出本地时间  
    std::cout << "Local time: " << std::put_time(now_tm, "%c") << std::endl;  
  
    return 0;  
}

```

## 获取UTC时间，也就是ISO时间

```c++

#include <iostream>  
#include <chrono>  
#include <ctime>  
#include <iomanip>  
  
int main() {  
    // 获取当前UTC时间  
    auto utc_now = std::chrono::utc_clock::now();  
    // 转换为time_t  
    std::time_t utc_now_c = std::chrono::utc_clock::to_time_t(utc_now);  
  
    // 转换为tm结构  
    std::tm* utc_tm = std::gmtime(&utc_now_c);  
  
    // 输出UTC时间  
    std::cout << "UTC time: " << std::put_time(utc_tm, "%c") << std::endl;  
  
    return 0;  
}


```
