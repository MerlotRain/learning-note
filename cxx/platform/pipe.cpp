#ifdef _WIN32

#include <Windows.h>


#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief 通过pipe的方式启动一个子进程，并在子进程中调用
 * 
 */


#endif