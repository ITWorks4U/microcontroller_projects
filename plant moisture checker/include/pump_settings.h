#ifndef PUMP_SETTINGS_H
#define PUMP_SETTINGS_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

/////
/// constants
/////

#define DURATION_INIT_PUMP_IN_MS     250  // 250ms
#define MAX_ELAPSED_TIME_CTR_IN_SEC  5    // each pump may be active for 5 seconds

/////
/// structures
/////

typedef struct {
    bool is_running;                     // check, if thus pump is running
    int runtime_counter;                 // runtime counter for this pump
} Pump;

#endif