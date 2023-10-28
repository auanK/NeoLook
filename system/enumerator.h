#ifndef ENUMERATOR_H
#define ENUMERATOR_H

typedef enum priority_policy priority_policy;
enum priority_policy{
    FCFS,
    SJF
};
#endif

//enumerator para os eventos do simulador
typedef enum event_type event_type;
enum event_type{
    PROCESS_ARRIVAL,
    PROCESS_EXIT,
    PROCESS_CPU_REQUEST,
    PROCESS_CPU_RELEASE,
    PROCESS_DISK_1_REQUEST,
    PROCESS_DISK_1_RELEASE,
    PROCESS_DISK_2_REQUEST,
    PROCESS_DISK_2_RELEASE,
    PROCESS_NETWORK_REQUEST,
    PROCESS_NETWORK_RELEASE,
    PROCESS_ARRIVAL_CPU,
    PROCESS_ARRIVAL_DISK_1,
    PROCESS_ARRIVAL_DISK_2,
    PROCESS_ARRIVAL_NETWORK,
    PROCESS_EXIT_CPU,
    PROCESS_EXIT_DISK_1,
    PROCESS_EXIT_DISK_2,
    PROCESS_EXIT_NETWORK
};