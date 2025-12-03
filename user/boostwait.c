
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int main(void) {
    struct procinfo info;
    
    printf("=== Waiting for Automatic Boost ===\n");
    printf("This will run until tick 100+ to trigger boost\n\n");
    
    int last_priority = 0;
    
    // Run for a LONG time
    for(int i = 0; i < 50000000; i++) {
        volatile long sum = 0;
        for(int j = 0; j < 100; j++) {
            sum += j;
        }
        
        // Check status frequently
        if(i % 5000000 == 0) {
            getprocinfo(&info);
            printf("Iteration %d: Priority %d, Runtime: %ld\n",
                   i/5000000, info.priority, info.runtime);
            
            // Detect boost
            if(info.priority < last_priority) {
                printf("\n*** AUTOMATIC BOOST DETECTED! ***\n");
                printf("Priority went from %d to %d\n\n", 
                       last_priority, info.priority);
            }
            last_priority = info.priority;
        }
    }
    
    getprocinfo(&info);
    printf("\nFinal: Priority %d, Runtime: %ld\n", 
           info.priority, info.runtime);
    
    exit(0);
}