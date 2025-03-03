#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(2, "sleep: Command format: sleep <ticks>\n");
        exit(1);
    }

    int ticks = atoi(argv[1]);
    if (ticks <= 0) {
        fprintf(2, "sleep: Invalid number of ticks\n");
        exit(1);
    }

    fprintf(2, "(nothing happens for a little while)\n");
    sleep(ticks);

    exit(0);
}