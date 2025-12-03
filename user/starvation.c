#include "kernel/types.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int main(void) {
    printf("=== Starvation Prevention Test ===\n");
    printf("This test runs for ~150 ticks to trigger priority boosting\n\n");
    
    struct procinfo info;
    int last_priority = 0;
    int boost_detected = 0;
    
    // Phase 1: Demote to lowest priority
    printf("Phase 1: Demoting to lowest priority...\n");
    for(int i = 0; i < 5000000; i++) {
        volatile int x = i * 2;
        (void)x;
        
        if(i % 1000000 == 0) {
            getprocinfo(&info);
            printf("  Iteration %d - Priority: %d, Runtime: %ld\n",
                   i/1000000, info.priority, info.runtime);
            last_priority = info.priority;
        }
    }
    
    printf("\nPhase 2: Waiting for priority boost...\n");
    printf("(Should see boost around tick 100)\n\n");
    
    // Phase 2: Continue working and watch for boost
    for(int i = 0; i < 1000000000; i++) {
        volatile int x = i * 2;
        (void)x;
        
        if(i % 1000000 == 0) {
            getprocinfo(&info);
            printf("  Iteration %d - Priority: %d, Runtime: %ld\n",
                   i/1000000, info.priority, info.runtime);
            
            // Detect if we got boosted
            if(info.priority < last_priority) {
                printf("  *** BOOST DETECTED! Priority went from %d to %d ***\n",
                       last_priority, info.priority);
                boost_detected = 1;
            }
            last_priority = info.priority;
        }
    }
    
    getprocinfo(&info);
    printf("\nFinal state: Priority %d, Runtime: %ld\n", 
           info.priority, info.runtime);
    
    if(boost_detected) {
        printf("\n✓ SUCCESS: Priority boosting working!\n");
    } else {
        printf("\n✗ WARNING: No boost detected (may need to run longer)\n");
    }
    
    exit(0);
}