#ifndef RESOURCE_H
#define RESOURCE_H
#include "computer.h"
#include "enumerator.h"
#include "process.h"

template <typename Type>
class resource{
    private:
    computer<Type> *computer;
    Type *network;
    int amount;
    priority_policy policy;

    public:
    resource(int amount, priority_policy policy){
        this->amount = amount;
        this->policy = policy;
        this->computer = new computer<Type>();
        this->network = new Type();
        
        if(policy == SJF){
            this->computer->cpu->set_comparator(&compare_process_cpu);
            this->computer->disk_1->set_comparator(&compare_process_disk);
            this->computer->disk_2->set_comparator(&compare_process_disk);
            this->network->set_comparator(&compare_process_network);
        }
    }

};
#endif