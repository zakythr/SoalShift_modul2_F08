#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main () {
  
  // argv[n] = { {your-program-name}, {argument[1]}, {argument[2]},.....,{argument[n-2]}, NULL }
  char *argv[3] = {"killall", "test_nomer5", NULL};
  execv("/usr/bin/killall", argv);

  return 0;
}

