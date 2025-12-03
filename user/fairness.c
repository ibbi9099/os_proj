#include "kernel/types.h"
#include "user/user.h"
#include "kernel/procinfo.h"

void worker(int id) {
  struct procinfo info;
  
  printf("Worker %d starting (PID %d)\n", id, getpid());
  
  // Do lots of work
  for(int i = 0; i < 50000000; i++) {
    volatile int x = i * 2;
    (void)x;
    
    if(i % 10000000 == 0) {
      getprocinfo(&info);
      printf("Worker %d: Priority %d, Runtime %ld\n", 
             id, info.priority, info.runtime);
    }
  }
  
  getprocinfo(&info);
  printf("Worker %d DONE - Final: Priority %d, Runtime %ld\n", 
         id, info.priority, info.runtime);
}

int main(void) {
  printf("=== Fairness Test: 3 CPU-bound processes ===\n\n");
  
  int n = 3;
  
  for(int i = 0; i < n; i++) {
    int pid = fork();
    if(pid == 0) {
      // Child process
      worker(i + 1);
      exit(0);
    }
  }
  
  // Parent waits for all children
  for(int i = 0; i < n; i++) {
    wait(0);
  }
  
  printf("\n=== All workers completed ===\n");
  exit(0);
}