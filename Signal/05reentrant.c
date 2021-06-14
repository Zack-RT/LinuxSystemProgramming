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

typedef struct{
    int a; int b;
}TEST;

TEST g_data;

void handler(int sig)
{
    printf("%d %d\n", g_data.a, g_data.b);
    alarm(1);
}

int main()
{
    TEST zeros = {0, 0};
    TEST ones = {1, 1};

    sig_t ret = signal(SIGALRM, handler);
    if (ret == SIG_ERR){
        ERR_EXIT("signal error");
    }
    g_data = zeros;
    alarm(1);
    while (1)
    {
        // 这两条语句并非一个原子操作，可能ab两个字段分开赋值，信号可能在这个过程中产生中断
        // 中断处理程序和被中断之前的程序如果访问共享的数据就会出现不可预料的情况
        g_data = zeros; 
        g_data = ones;
    }
    
    return 0;
    
}