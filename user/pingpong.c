#include "kernel/types.h"
#include "user/user.h"

int 
main(){
    int p[2];
    char buffer;
    pipe(p);
    int pid = fork();

    if (pid == 0){
        read(p[0], &buffer, 1);
        write(p[1], "x", 1);
        wait(0);
        printf("%d: received ping\n", getpid());
        exit(0);
    } 
    else{
        write(p[1], "x", 1);
        wait(0);
        read(p[0], &buffer, 1);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
}
