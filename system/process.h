#ifndef PROCESS_H
#define PROCESS_H

class process{
    public:
    int instant;
    int demand_cpu;
    int demand_disk;
    int demand_network;

    process(int instant, int demand_cpu, int demand_disk, int demand_network){
        this->instant = instant;
        this->demand_cpu = demand_cpu;
        this->demand_disk = demand_disk;
        this->demand_network = demand_network;
    }
};

#endif