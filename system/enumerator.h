#ifndef ENUMERATOR_H
#define ENUMERATOR_H

typedef enum priority_policy priority_policy;
enum priority_policy{
    FCFS,
    SJF
};

typedef enum type_event type_event;
enum type_event{
    INITIALIZE_PROCESS,
    ACESS_CPU,
    ACESS_DISK,
    ACESS_NETWORK,
    FINISH_PROCESS
};
#endif

