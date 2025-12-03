#include "kernel/types.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int main(void) {
  struct procinfo info;
  
  printf("=== Clean MLFQ Test ===\n");
  
  for(int i = 0; i < 20; i++) {
    // Do significant work
    volatile long sum = 0;
    for(int j = 0; j < 2000000; j++) {
      sum += j;
    }
    
    getprocinfo(&info);
    printf("Step %2d: Priority %d, Runtime %ld\n", i, info.priority, info.runtime);

  }
  
  exit(0);
}
