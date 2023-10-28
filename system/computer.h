#pragma once

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

    void add_process(process process) {
        cpu->push(process.demand_cpu);

        if (disk_1->empty() && disk_2->empty() || !disk_1->empty() &&
            !disk_2->empty()) {
            if (rand() % 2 == 0) {
                disk_1->push(process.demand_disk);
            } else {
                disk_2->push(process.demand_disk);
            }
        } else if (disk_1->empty()) {
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
