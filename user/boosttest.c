
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int main(void) {
    struct procinfo info;
    
    printf("=== Manual Boost Test ===\n\n");
    
    // Step 1: Demote to low priority
    printf("Step 1: Demoting to low priority...\n");
    for(int i = 0; i < 3000000; i++) {
        volatile int x = i * 2;
        (void)x;
    }
    
    getprocinfo(&info);
    printf("After demotion: Priority %d, Runtime: %ld\n\n",
           info.priority, info.runtime);
    
    if(info.priority == 0) {
        printf("Note: Still at priority 0, doing more work...\n");
        for(int i = 0; i < 5000000; i++) {
            volatile int x = i * 2;
            (void)x;
        }
        getprocinfo(&info);
        printf("After more work: Priority %d, Runtime: %ld\n\n",
               info.priority, info.runtime);
    }
    
    // Step 2: Trigger manual boost
    printf("Step 2: Triggering manual boost...\n");
    boostproc();
    
    // Step 3: Check priority
    getprocinfo(&info);
    printf("After boost: Priority %d, Runtime: %ld\n\n",
           info.priority, info.runtime);
    
    if(info.priority == 0) {
        printf("✓ SUCCESS: Manual boost working!\n");
    } else {
        printf("✗ FAIL: Priority should be 0, got %d\n", info.priority);
    }
    
    exit(0);
}