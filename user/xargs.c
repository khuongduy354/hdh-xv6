#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXLEN 512  

int main(int argc, char *argv[]) {
    char buf[MAXLEN];  
    char *cmd[MAXARG]; 
    int i, n = 0;
    int base_args = 1;
    int single_arg_mode = 0;
    if (argc > 2 && strcmp(argv[1], "-n") == 0 && strcmp(argv[2], "1") == 0) {
        single_arg_mode = 1;
        base_args = 3; 
    }
    for (i = base_args; i < argc && i < MAXARG - 1; i++) {
        cmd[i - base_args] = argv[i];
    }
    int fixed_args = argc - base_args;
    int arg_count = fixed_args;
    while ((n = read(0, buf, sizeof(buf))) > 0) {
        int j = 0;
        for (i = 0; i < n; i++) {
            if (buf[i] == '\n') {  
                buf[i] = 0;  
    
                cmd[fixed_args] = buf + j; // Thêm đối số mới
                cmd[fixed_args + 1] = 0;   // Đảm bảo danh sách tham số kết thúc bằng NULL
    
                if (fork() == 0) {
                    exec(cmd[0], cmd);
                    fprintf(2, "exec failed\n");
                    exit(1);
                } else {
                    wait(0);
                }
    
                j = i + 1; // Chuyển sang tham số tiếp theo
                fixed_args = argc - base_args; // Luôn đặt lại để không gộp nhiều dòng
            }
        }
    }
    if (!single_arg_mode) {
        cmd[arg_count] = 0;
        if (fork() == 0) {
            exec(cmd[0], cmd);
            fprintf(2, "exec failed\n");
            exit(1);
        }
        wait(0);
    }
    exit(0);
}
