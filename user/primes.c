#include "kernel/types.h"
#include "user/user.h"

void primes(int pipe_left[2]) __attribute__((noreturn));

void primes(int pipe_left[2]) {
    int p, n;
    int pipe_right[2];

    close(pipe_left[1]);

    if (read(pipe_left[0], &p, sizeof(p)) == 0) {
        close(pipe_left[0]);
        exit(0);
    }
    printf("prime %d\n", p);

    if (pipe(pipe_right) < 0) {
        fprintf(2, "Pipe creation failed\n");
        exit(1);
    }

    int pid = fork();
    if (pid < 0) {
        fprintf(2, "Fork failed\n");
        exit(1);
    }

    if (pid == 0) {
        close(pipe_left[0]);
        primes(pipe_right);
    } else {
        while (read(pipe_left[0], &n, sizeof(n)) > 0) {
            if (n % p != 0) {
                write(pipe_right[1], &n, sizeof(n));
            }
        }
        close(pipe_left[0]);
        close(pipe_right[1]);
        
        wait(0);
        exit(0);
    }
}

int 
main(){
    int pipe_main[2];
    pipe(pipe_main);

    if (fork() == 0)
        primes(pipe_main);
    else{
        for (int i = 2; i <= 280; i++)
            write(pipe_main[1], &i, sizeof(i));
        
        close(pipe_main[1]);
    
        wait(0);
        exit(0);
    }
}