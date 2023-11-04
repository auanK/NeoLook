#ifndef ESCALONATOR_H
#define ESCALONATOR_H
#include "enumerator.h"
#include "event.h"
#include "computer.h"
#include "../include/queue.h"
#include "resource.h"

template <typename Type>
class escalonator{
    public:
    queue<event*> events;
    resource<Type>* system;
    queue<process*>* process_queue;

    escalonator(int amount, priority_policy p, queue<process*>* process_queue){
        this->system = new resource<Type>(amount, p);
        this->process_queue = process_queue;
    }

    void print_event(){
        for(int i = 0; i < events.size(); i++){

            event* p = events.pop();

            switch(p->type){
                case INITIALIZE_PROCESS:
                    printf("INITIALIZE_PROCESS\n");
                    break;
                case WAIT_CPU:
                    printf("WAIT_CPU\n");
                    break;
                case ACCESS_CPU:
                    printf("ACCESS_CPU\n");
                    break;
                case WAIT_DISK:
                    printf("WAIT_DISK\n");
                    break;
                case ACCESS_DISK:
                    printf("ACCESS_DISK\n");
                    break;
                case WAIT_NETWORK:
                    printf("WAIT_NETWORK\n");
                    break;
                case ACCESS_NETWORK:
                    printf("ACCESS_NETWORK\n");
                    break;
                case FINISH_PROCESS:
                    printf("FINISH_PROCESS\n");
                    break;
            }

            p->processo->print();
            printf("\n");
        }
    }

    void run(){

        int time = 0;

        while (true) {

            printf("time: %d\n", time);

            bool flag = false;

            for(int i = 0; i < this->system->amount; i++){
                
                if(!this->system->computer_type[i].cpu->empty() || 
                   !this->system->computer_type[i].disk_1->empty() || 
                   !this->system->computer_type[i].disk_2->empty() ||
                   !this->system->network->empty() ||
                   this->system->computer_type[i].running_cpu != nullptr ||
                   this->system->computer_type[i].running_disk_1 != nullptr ||
                   this->system->computer_type[i].running_disk_2 != nullptr ||
                   this->system->running_network != nullptr){

                    flag = true;
                }

                if(flag) break;
            }

            if (process_queue->size() == 0 && !flag) {
                break;
            }

            while (!process_queue->empty() && process_queue->front()->instant == time) {
                process* p = process_queue->pop();

                // REGISTRAR EVENTO inicio do processo
                events.push(new event(time, INITIALIZE_PROCESS, new process(p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));
                events.push(new event(time, WAIT_CPU, new process(p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));


                system->add_process(p);
            }

            for(int i = 0; i < system->amount; i++){


                // PROCESS_CPU

                if(this->system->computer_type[i].running_cpu == nullptr){
                    process* p = this->system->computer_type[i].cpu->pop();

                    if(p != nullptr){
                        this->system->computer_type[i].running_cpu = p;

                        // REGISTRAR EVENTO inicio do processamento
                        events.push(new event(time, ACCESS_CPU, new process(p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));
                    }
                }else{
                    this->system->computer_type[i].consume_cpu();

                    if(this->system->computer_type[i].running_cpu->demand_cpu == 0){
                        process* p = this->system->computer_type[i].running_cpu;
                        this->system->computer_type[i].running_cpu = nullptr;

                        // REGISTRAR EVENTO final do processamento, esperando disco
                        events.push(new event(time, WAIT_DISK, new process(p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                        this->system->computer_type[i].add_process_disk();
                    }
                }

                // PROCESS_DISK_1

                if(this->system->computer_type[i].running_disk_1 == nullptr){

                    process* p = this->system->computer_type[i].disk_1->pop();

                    if(p != nullptr){
                        
                        p->print();

                        this->system->computer_type[i].running_disk_1 = p;

                        // REGISTRAR EVENTO inicio do acesso ao disco
                        events.push(new event(time, ACCESS_DISK, new process(p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));
                    }
                }

                // PROCESS_DISK_2

                if(this->system->computer_type[i].running_disk_2 == nullptr){
                    process* p = this->system->computer_type[i].disk_2->pop();

                    if(p != nullptr){

                        p->print();

                        this->system->computer_type[i].running_disk_2 = p;

                        // REGISTRAR EVENTO inicio do acesso ao disco
                        events.push(new event(time, ACCESS_DISK, new process(p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));
                    }
                }

                // CONSUME_DISK

                this->system->computer_type[i].consume_disk();

                process* disk1_p = this->system->computer_type[i].running_disk_1;
                process* disk2_p = this->system->computer_type[i].running_disk_2;

                
                if(disk1_p != nullptr && disk1_p->demand_disk == 0){
                    process* p = disk1_p;
                    this->system->computer_type[i].running_disk_1 = nullptr;

                    // REGISTRAR EVENTO final do acesso ao disco
                    events.push(new event(time, WAIT_NETWORK, new process(p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                    this->system->network->push(p);
                }

                if(disk2_p != nullptr && disk2_p->demand_disk == 0){
                    process* p = disk2_p;
                    this->system->computer_type[i].running_disk_2 = nullptr;

                    // REGISTRAR EVENTO final do acesso ao disco
                    events.push(new event(time, WAIT_NETWORK, new process(p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                    this->system->network->push(p);
                }

                // PROCESS_NETWORK

                if(this->system->running_network == nullptr){
                    process* p = this->system->network->pop();

                    if(p != nullptr){
                        this->system->running_network = p;

                        // REGISTRAR EVENTO inicio do acesso a rede
                        events.push(new event(time, ACCESS_NETWORK, new process(p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));
                    }
                }else{
                    this->system->running_network->demand_network--;

                    if(this->system->running_network->demand_network == 0){
                        process* p = this->system->running_network;
                        this->system->running_network = nullptr;

                        // REGISTRAR EVENTO final do acesso a rede
                        events.push(new event(time, FINISH_PROCESS, new process(p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                        delete p;
                    }
                
                }
            }
            time++;
        }

    }

    ~escalonator(){
    }
    
};

#endif