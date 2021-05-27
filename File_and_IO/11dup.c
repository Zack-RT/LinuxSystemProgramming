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

int main(void)
{
    int fd = open("test.txt", O_RDWR);
    if(fd == -1){
        ERR_EXIT("open");
    }
    close(1); // close standard output
    dup(fd); // 此时新的fd序号为1
    printf("hello\n"); // 此时printf不会输出到stdout了，而是输入到文件中
    
    return 0;
}