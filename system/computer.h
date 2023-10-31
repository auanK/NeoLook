#ifndef COMPUTER_H
#define COMPUTER_H

#include "../include/min_heap.h"
#include "../include/queue.h"
#include "enumerator.h"
#include "process.h"

#include <iostream>

using namespace std;
template <typename Type>
class computer {
   public:
    Type* cpu;
    Type* disk_1;
    Type* disk_2;

    computer() {
        cpu = new Type();
        disk_1 = new Type();
        disk_2 = new Type();
    }

    ~computer() {
        delete cpu;
        delete disk_1;
        delete disk_2;
    }

    void add_process_cpu(process process) {
        // process.demand_cpu eh um inteiro
        // precisamos adicionar um processo ao computador
        cpu->push(process.demand_cpu);

        // criar um metodo add_process_disk para adicionar o processo da vez
        // para acesso a um dos discos
        srand(time(NULL));
        
            if (rand() % 2 == 0) {
                disk_1->push(process.demand_disk);
            } else {
                disk_2->push(process.demand_disk);
            } 
    }

    
    void print() {
        cout << "CPU: ";
        cpu->print();
        cout << "Disk 1: ";
        disk_1->print();
        cout << "Disk 2: ";
        disk_2->print();
    }
};

#endif