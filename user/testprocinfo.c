// simpleprocinfo.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int main(void) {
    struct procinfo info;
    
    printf("=== getprocinfo System Call Test ===\n\n");
    
    // Get initial state
    if(getprocinfo(&info) < 0) {
        printf("ERROR: getprocinfo failed!\n");
        exit(1);
    }
    
    printf("Process Information:\n");
    printf("  PID:        %d\n", getpid());
    printf("  Priority:   %d\n", info.priority);
    printf("  Runtime:    %ld ticks\n", info.runtime);

    
    printf("Doing some work...\n");
    volatile int sum = 0;
    for(int i = 0; i < 1000000; i++) {
        sum += i;
    }
    
    // Get state after work
    getprocinfo(&info);
    printf("\nAfter computation:\n");
    printf("  Priority:   %d\n", info.priority);
    printf("  Runtime:    %ld ticks\n", info.runtime);
 
    
    printf("SUCCESS: getprocinfo syscall working!\n");
    exit(0);
}