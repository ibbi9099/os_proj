#include "kernel/types.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int main(void) {
    printf("=== Long-Running Fairness Test ===\n");
    printf("Running CPU and I/O processes for ~200 ticks\n\n");
    
    int cpu_pid = fork();
    if(cpu_pid == 0) {
        // CPU-bound child
        struct procinfo info;
        printf("CPU-bound starting (PID: %d)\n", getpid());
        
        for(int round = 0; round < 20; round++) {
            // Heavy computation
            volatile long sum = 0;
            for(long i = 0; i < 10000000; i++) {
                sum += i;
            }
            
            getprocinfo(&info);
            printf("CPU round %d: Priority %d, Runtime: %ld\n",
                   round, info.priority, info.runtime);
        }
        
        getprocinfo(&info);
        printf("CPU-bound final: Priority %d, Runtime: %ld\n",
               info.priority, info.runtime);
        exit(0);
    }
    
    sleep(5);  // Let CPU process start first
    
    int io_pid = fork();
    if(io_pid == 0) {
        // I/O-bound child
        struct procinfo info;
        printf("I/O-bound starting (PID: %d)\n", getpid());
        
        for(int i = 0; i < 30; i++) {
            getprocinfo(&info);
            printf("I/O op %d: Priority %d, Runtime: %ld\n",
                   i, info.priority, info.runtime);
            sleep(10);  // I/O wait
        }
        
        getprocinfo(&info);
        printf("I/O-bound final: Priority %d, Runtime: %ld\n",
               info.priority, info.runtime);
        exit(0);
    }
    
    // Parent waits for both
    wait(0);
    wait(0);
    
    printf("\n=== Long-Running Test Complete ===\n");
    printf("Check that:\n");
    printf("  1. Both processes made progress\n");
    printf("  2. Boost occurred around tick 100 and 200\n");
    printf("  3. No starvation observed\n");
    
    exit(0);
}