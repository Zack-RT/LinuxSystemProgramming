#include <stdio.h>
#include <unistd.h>

extern char**__environ;

int main()
{
    printf("Here is hello, pid=%d\n", getpid());
    for(int i = 0; __environ[i]; ++i){
        printf("%s\n", __environ[i]);
    }
    return 0;
}