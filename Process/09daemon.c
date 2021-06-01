#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <wait.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

int setup_daemon(void)
{
    pid_t pid;
    pid = fork();
    if(pid < 0){
        ERR_EXIT("fork error");
    }
    if(pid > 0){
        exit(EXIT_SUCCESS);
    }
    setsid(); // 创建新的会话，如果是进程组组长则会失败，所以创建一个子进程来做，让父进程退出
    chdir("/");  // 修改工作目录为根目录
    int i;
    for(i=0; i<3; ++i){
        close(i);
    }
    open("/dev/null", O_RDWR); // 此时打开的fd=0，为标准输入
    dup(0); // 标准输出
    dup(0); // 标准错误输出
    return 0;
}

int main(int argc, char **argv)
{
    setup_daemon();
    printf("test ...\n");
    while(1){
        sleep(2);
    }
    return 0;
}


