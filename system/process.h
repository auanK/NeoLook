#ifndef PROCESS_H
#define PROCESS_H

// classe contendo as demandas dos processsos para cada recurso.
class process{
    public:
    int instant;
    int demand_cpu;
    int demand_disk;
    int demand_network;

    process(int demand_cpu, int demand_disk, int demand_network, int instant){
        this->instant = instant;
        this->demand_cpu = demand_cpu;
        this->demand_disk = demand_disk;
        this->demand_network = demand_network;
    }
};

#endif