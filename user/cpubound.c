#include "kernel/types.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int main(void) {
    struct procinfo info;
    printf("CPU-bound process starting (PID: %d)\n", getpid());
    
    // Much more work to trigger multiple demotions
    volatile int sum = 0;  // Make it volatile AND use it
    for(int i = 0; i < 10000000; i++) {
        for(int j = 0; j < 100; j++) {
            sum += i * j;  // Actually use the result
        }
        
        // Check priority periodically
        if(i % 1000000 == 0) {
            getprocinfo(&info);
            printf("  Progress: %d%% - Priority: %d, Runtime: %ld\n",
                   i/100000, info.priority, info.runtime);
        }
    }
    
    getprocinfo(&info);
    printf("CPU-bound done - Final Priority: %d, Runtime: %ld, Sum: %d\n",
           info.priority, info.runtime, sum);
    exit(0);
}