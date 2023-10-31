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

int compare_process_cpu(process* a, process* b){
    if(a->demand_cpu < b->demand_cpu){
        return -1;
    }else if(a->demand_cpu > b->demand_cpu){
        return 1;
    }else{
        return 0;
    }
}

int compare_process_disk(process* a, process* b){
    if(a->demand_disk < b->demand_disk){
        return -1;
    }else if(a->demand_disk > b->demand_disk){
        return 1;
    }else{
        return 0;
    }
}

int compare_process_network(process* a, process* b){
    if(a->demand_network < b->demand_network){
        return -1;
    }else if(a->demand_network > b->demand_network){
        return 1;
    }else{
        return 0;
    }
}

#endif