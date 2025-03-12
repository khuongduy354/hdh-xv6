#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(2, "Usage: trace <mask> <command> [arguments...]\n");
    exit(1);
  }

  int mask = atoi(argv[1]);
  if (mask < 0) {
    fprintf(2, "mask must be a positive number\n");
    exit(1);
  }

  if (trace(mask) < 0) {
    fprintf(2, "trace failed\n");
    exit(1);
  }

  char *command = argv[2];
  char *new_argv[argc - 1]; // Array to hold the command and its arguments

  // Copy command and its arguments to new_argv
  for (int i = 2; i < argc; i++) {
    new_argv[i - 2] = argv[i];
  }
  new_argv[argc - 2] = 0; // Null-terminate the array

  exec(command, new_argv);
  fprintf(2, "exec %s failed\n", command);
  exit(1);
}
