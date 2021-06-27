#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)
#define TEST_SIZE 68*1024

int main()
{
    char a[TEST_SIZE];
    char b[TEST_SIZE];
    memset(a, 'A', sizeof(a));
    memset(b, 'B', sizeof(b));
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1){
        ERR_EXIT("pipe error");
    }
    pid_t pid = fork();
    if(pid == -1){
        ERR_EXIT("fork error");
    }
    if(pid == 0){
        close(pipefd[0]);
        ret = write(pipefd[1], a, sizeof(a));
        printf("apid=%d write %d bytes to pipe\n", getpid(), ret);
        exit(EXIT_SUCCESS);
    }
    pid = fork();
    if(pid == 0){
        close(pipefd[0]);
        ret = write(pipefd[1], b, sizeof(b));
        printf("bpid=%d write %d bytes to pipe\n", getpid(), ret);
        exit(EXIT_SUCCESS);
    }
    close(pipefd[1]);
    sleep(1);
    int fd = open("/tmp/test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buf[1<<12] = {0};
    int n = 1;
    while(1){
        ret = read(pipefd[0], buf, sizeof(buf));
        if(ret == 0){
            break;
        }
        printf("n=%02d, pid=%d read %d bytes from pipe, buf[4095]=%c\n", 
                n++, getpid(), ret, buf[4095]);
        write(fd, buf, ret);
    }
    return 0;
}