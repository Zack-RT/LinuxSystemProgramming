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

int main()
{
    int pipefd[2];
    pipe(pipefd);
    int flg = fcntl(pipefd[1], F_GETFL);
    fcntl(pipefd[1], F_SETFL, flg | O_NONBLOCK);
    int count = 0;
    while(1){
        int ret = write(pipefd[1], "A", 1);
        if (ret == -1){
            printf("%s\n",strerror(errno));
            break;
        }
        else{
            count += ret;
        }
    }
    printf("pipe size = %d\n", count);
    return 0;
}