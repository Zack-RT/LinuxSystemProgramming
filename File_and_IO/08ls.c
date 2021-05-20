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

int main(void)
{
    DIR *dir = opendir(".");
    struct dirent *de;
    while ((de = readdir(dir)) != NULL)
    {
        printf("%s\n", de->d_name);
    }
    closedir(dir);
    exit(EXIT_SUCCESS);
}