/**
 * @brief  不同平台下，打开动态库并获取一个符号的操作
 */

#include <string>

#ifdef _WIN32

#include <Windows.h>

void load_module()
{
    // 不同编译器生成的文件名称不同，这里只列举MSVC和MINGW
#ifdef _MSC_VER
    std::string module_path = "calc.dll";
#elif defined(__MINGW32__)
    std::string module_path = "libcalc.dll";
#endif

    HMODULE hdl = LoadLibraryA(module_path.c_str());
    if (hdl)
    {
        // 定义函数指针
        typedef int (*fun_sum_pointer)(int, int);
        fun_sum_pointer fun = (fun_sum_pointer)GetProcAddress(hdl, "sum");
        if (!fun)
        {
            // log
        }
        int ret = fun(1, 2);
    }
    FreeModule(hdl);
}

#else

#include <dlfcn.h>
#include <stdlib.h>

void load_mudule()
{
#ifdef __APPLE__
    std::string module_path = "libcalc.dylib";
#else
    std::string module_path = "libcalc.so";
#endif

    void *hdl = dlopen(module_path.c_str(), RTLD_LAZY);
    if (!hdl)
    {
        // log
        dlerror();
    }

    typedef int (*fun_sum_pointer)(int, int);
    fun_sum_pointer fun = (fun_sum_pointer)dlsym(hdl, "sum"); // 使用dlsym捕获
    dlclose(hdl);
}

#endif //