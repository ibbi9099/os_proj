#define _PROCINFO_H_

#include "types.h"

struct procinfo {
  int pid;              // Process ID
  int priority;         // Current priority level (0-3)
  int state;            // Process state
  char name[16];        // Process name
  uint64 runtime;       // Total runtime ticks
};