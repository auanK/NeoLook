#ifndef ENUMERATOR_H
#define ENUMERATOR_H

typedef enum priority_policy { FCFS, SJF } priority_policy;

typedef enum type_event {
    INITIALIZE_PROCESS,
    WAIT_CPU,
    ACCESS_CPU,
    WAIT_DISK,
    ACCESS_DISK,
    WAIT_NETWORK,
    ACCESS_NETWORK,
    FINISH_PROCESS
} type_event;

#endif
