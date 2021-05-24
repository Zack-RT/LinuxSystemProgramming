#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

#define MAJOR(a) (int)((unsigned short)a >> 8) // 获取高8位
#define MINOR(a) (int)((unsigned short)a & 0xFF)  // 获取低8位

int filetype(struct stat *buf);
void fileperm(struct stat *buf, char *perm);

int main(int argc, char **argv)
{
    if (argc < 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("Filename: %s\n", argv[1]);
    struct stat sbuf;
    if(stat(argv[1], &sbuf) < 0){
        ERR_EXIT("stat error");
    }

    printf("File number: major %d, minor %d, inode %d\n", \
        MAJOR(sbuf.st_dev), MINOR(sbuf.st_dev), (int)sbuf.st_ino);

    int ret = filetype(&sbuf);
    if(ret){
        printf("Device number: major %d, minor %d\n", MAJOR(sbuf.st_rdev), MINOR(sbuf.st_rdev));
    }
    char perm[11] = "-----------";
    fileperm(&sbuf, perm);
    printf("File permission bits=%o_%s\n", \
        sbuf.st_mode & 07777, perm);

    return 0;
}

int filetype(struct stat *buf)
{
    int flag = 0;
    printf("Filetype:");
    mode_t mode = buf->st_mode;
    switch (mode & S_IFMT)
    {
    case S_IFSOCK:
        printf("socket\n");
        break;
    case S_IFLNK:
        printf("symbolic link\n");
        break;
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFBLK:
        printf("block device\n");
        flag = 1;
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        flag = 1;
        break;
    case S_IFIFO:
        printf("FIFO\n");
        break;
    default:
        printf("undefine type file\n");
        break;
    }
    return flag;
}

void fileperm(struct stat *buf, char *perm)
{
    mode_t mode = buf->st_mode;
    switch (mode & S_IFMT)
    {
    case S_IFSOCK:
        perm[0] = 's';
        break;
    case S_IFLNK:
        perm[0] = 'l';
        break;
    case S_IFREG:
        perm[0] = '-';
        break;
    case S_IFBLK:
        perm[0] = 'b';
        break;
    case S_IFDIR:
        perm[0] = 'd';
        break;
    case S_IFCHR:
        perm[0] = 'c';
        break;
    case S_IFIFO:
        perm[0] = 'p';
        break;
    default:
        perm[0] = '?';
        break;
    }
    if(mode & S_IRUSR){
        perm[1] = 'r';
    }
    if(mode & S_IWUSR){
        perm[2] = 'w';
    }
    if(mode & S_IXUSR){
        perm[3] = 'x';
    }
    if(mode & S_IRGRP){
        perm[4] = 'r';
    }
    if(mode & S_IWGRP){
        perm[5] = 'w';
    }
    if(mode & S_IXGRP){
        perm[6] = 'x';
    }
    if(mode & S_IROTH){
        perm[7] = 'r';
    }
    if(mode & S_IWOTH){
        perm[8] = 'w';
    }
    if(mode & S_IXOTH){
        perm[9] = 'x';
    }
    perm[10] = '\0';

    return;
}