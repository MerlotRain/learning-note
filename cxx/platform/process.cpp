#ifdef _WIN32

#else

/*

https://blog.csdn.net/itworld123/article/details/125158725

我们需要进程间通信，所以需要管道，所以核心在于进程。
进程不是简单fork一下，还需要执行子程序，还需要捕获结果，所以我们先介绍如果调用一个子程序

exec系列函数

用 exec 函数可以把当前进程替换为一个新进程，且新进程与原进程有相同的 PID。exec
名下是由多个关联函数组成的一个完整系列。

int execl(const char *path, const char *arg, ...);

int execlp(const char *file, const char *arg, ...);

int execle(const char *path, const char *arg, ..., char * const envp[]);

int execv(const char *path, char *const argv[]);

int execvp(const char *file, char *const argv[]);

path 参数表示你要启动程序的名称包括路径名。

argv 参数表示启动程序所带的参数，一般第一个参数为要执行命令名，不是带路径且 arg
必须以NULL 结束

返回值：成功返回 0，失败返回 -1。


带`l`的表示，后边的参数以可变参数的形式给出且都以一个空指针结束。

execl("/bin/ls","ls","-l",NULL);

带`p`的表示，路径可以不是完整的，但需要在`PATH`中查找
 */

#endif //