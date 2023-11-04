#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>

#include "../include/min_heap.h"
#include "../include/queue.h"
#include "enumerator.h"
#include "process.h"

using namespace std;
template <typename Type>
class computer {
   public:
    Type* cpu;
    Type* disk_1;
    Type* disk_2;
    process* running_cpu;
    process* running_disk_1;
    process* running_disk_2;

    computer() {
        cpu = new Type();
        disk_1 = new Type();
        disk_2 = new Type();
        running_cpu = nullptr;
        running_disk_1 = nullptr;
        running_disk_2 = nullptr;
    }

    ~computer() {
        delete cpu;
        delete disk_1;
        delete disk_2;
    }

    void add_process_cpu(process* process) {
        cpu->push(process);
        if (running_cpu == nullptr) {
            running_cpu = cpu->pop();
        }
    }

    void add_process_disk() {
        Type p = cpu->pop();

        int random = rand() % 2;

        if (random == 0) {
            disk_1->push(p);
        } else {
            disk_2->push(p);
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