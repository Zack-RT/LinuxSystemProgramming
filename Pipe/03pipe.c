#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>

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
        sleep(3);
        close(pipefd[0]);
        write(pipefd[1], "hello\n", 6);
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }

    close(pipefd[1]);
    char recvbuf[10] = {0};
    int flg = fcntl(pipefd[0], F_GETFL);
    fcntl(pipefd[0], F_SETFL, flg | O_NONBLOCK);
    int ret = read(pipefd[0], recvbuf, sizeof(recvbuf));
    if (ret < 0){
        ERR_EXIT("read error");
    }
    write(STDOUT_FILENO, recvbuf, strlen(recvbuf));

    wait(NULL);
    return 0;
}