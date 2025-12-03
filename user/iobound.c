#include "kernel/types.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int main(void) {
    struct procinfo info;
    printf("I/O-bound process starting (PID: %d)\n", getpid());
    
    for(int i = 0; i < 20; i++) {
        getprocinfo(&info);
        printf("I/O op %d - Priority: %d, Runtime: %ld\n", 
               i, info.priority, info.runtime);
        sleep(10);
    }
    
    printf("I/O-bound process done\n");
    exit(0);
}