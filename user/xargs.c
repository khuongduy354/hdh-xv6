#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXLEN 512  

int main(int argc, char *argv[]){
    char buf[MAXLEN];  
    char *cmd[MAXARG]; 
    int i, n = 0;

    for (i = 1; i < argc && i < MAXARG - 1; i++)
        cmd[i - 1] = argv[i];

    while ((n = read(0, buf, sizeof(buf))) > 0){
        int j = 0;
        for (i = 0; i < n; i++){
            if (buf[i] == '\n'){  
                buf[i] = 0;  
                cmd[argc - 1] = buf + j;  
                cmd[argc] = 0;  

                if (fork() == 0){
                    exec(cmd[0], cmd);
                    exit(1);
                }
                else
                    wait(0);
                j = i + 1;
            }
        }
    }
    exit(0);
}
