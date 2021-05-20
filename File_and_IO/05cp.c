#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

int main(int argc, char **argv)
{
    if(argc < 3){
        fprintf(stderr ,"Usage: %s <src> <dest>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int infd = open(argv[1], O_RDONLY);
    if(infd < 0){
        ERR_EXIT("open");
    }
    int outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(outfd < 0){
        ERR_EXIT("open");
    }
    char readbuf[1024] = {0};
    int nread;
    while ((nread = read(infd, &readbuf, sizeof(readbuf))) > 0)
    {
        write(outfd, readbuf, nread);
    }
    close(infd);
    close(outfd);
    return 0;
}