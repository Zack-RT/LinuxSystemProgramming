#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

int main()
{
    int pipefd[2];
    if(pipe(pipefd) < 0){
        ERR_EXIT("pipe error");
    }
    pid_t pid = fork();
    if(pid < 0){
        ERR_EXIT("fork error");
    }
    if(pid == 0){
        dup2(pipefd[1], STDOUT_FILENO); // 将标准输出重定向到管道的写端
        close(pipefd[1]);
        close(pipefd[2]);
        execlp("ls", "ls", NULL); // 子进程运行ls
        fprintf(stderr, "error execlp ls\n"); // 上面成功就不会运行到次   
        exit(EXIT_FAILURE);
    }

    dup2(pipefd[0], STDIN_FILENO); // 将标准输入重定向到管道的读端
    close(pipefd[1]);
    close(pipefd[2]);
    execlp("wc", "wc", "-w", NULL);
    fprintf(stderr, "error execlp wc\n");
    wait(NULL);
    return 0;
}