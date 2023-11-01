#ifndef RESOURCE_H
#define RESOURCE_H
#include "computer.h"
#include "enumerator.h"
#include "process.h"

template <typename Type>
class resource{
    private:
    computer<Type*> *computer;
    Type *network;
    int amount;
    priority_policy policy;

    public:
    resource(int amount, priority_policy policy){
        this->amount = amount;
        this->policy = policy;
        this->computer = new computer<Type>()[amount];
        this->network = new Type();
        
        if(policy == SJF){
            for(int i = 0; i < amount; i++){
                this->computer->cpu->set_comparator(&compare_process_cpu);
                this->computer->disk_1->set_comparator(&compare_process_disk);
                this->computer->disk_2->set_comparator(&compare_process_disk);
            }

            this->network->set_comparator(&compare_process_network);
        }
    }

    void add_process(process* process){
        srand(time(NULL));
        int random = rand() % amount;
        computer[random].add_process_cpu(process);
    }

    ~resource(){
        delete[] computer;
        delete network;
    }
};
#endif