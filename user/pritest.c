#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int main(void) {
  struct procinfo info;
  
  printf("Testing priority changes...\n");
  
  for(int i = 0; i < 10; i++) {
    // Do LOTS of work to trigger many timer interrupts
    volatile int sum = 0;  // volatile prevents optimization
    for(int j = 0; j < 5000000; j++) {
      sum += j;
    }
    
    getprocinfo(&info);
    printf("Iteration %d - Priority: %d, Runtime: %ld, Sum: %d\n", 
           i, info.priority, info.runtime, sum);
  }
  
  exit(0);
}