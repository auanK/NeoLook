#ifndef ENUMERATOR_H
#define ENUMERATOR_H

typedef enum priority_policy { FCFS, SJF } priority_policy;

typedef enum type_event {
    INITIALIZE_PROCESS,
    ACCESS_CPU,
    ACCESS_DISK,
    ACCESS_NETWORK,
    FINISH_PROCESS
} type_event;

#endif
