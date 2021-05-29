#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

void my_exit1(void){
    printf("my exit1 ...\n");
}
void my_exit2(void){
    printf("my exit2 ...\n");
}

int main(int argc, char **argv)
{
    atexit(my_exit1);
    atexit(my_exit2);
    exit(0);
}
