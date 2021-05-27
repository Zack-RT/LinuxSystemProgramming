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
    int fd1;
    int fd2;
    char buf1[20] = {0};
    char buf2[20] = {0};
    fd1 = open("test.txt", O_RDONLY);
    fd2 = open("test.txt", O_RDWR);
    if(fd2 == -1 || fd1 == -1){
        ERR_EXIT("open");
    }

    // fd1与fd2对应不同的文件表，但是两个文件表都指向同一个v节点表
    read(fd1, buf1, 5);
    printf("buf1=%s\n", buf1);

    read(fd2, buf2, 5);
    printf("buf2=%s\n", buf2);

    write(fd2, "AAAAA", 5);
    memset(buf1, 0, sizeof(buf1));
    read(fd1, buf1, 5);
    printf("buf1=%s\n", buf1);

    close(fd1);
    close(fd2);
    return 0;
}