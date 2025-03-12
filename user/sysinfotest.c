#include "kernel/sysinfo.h"
#include "user.h"

int
main(){
    struct sysinfo info;
    
    if (sysinfo(&info) < 0){
        printf("sysinfotest: sysinfo failed\n");
        exit(1);
    }

    printf("free memory: %ld bytes\n", info.freemem);
    printf("active processes: %ld\n", info.nproc);
    printf("sysinfotest: OK\n");

    exit(0);
}
