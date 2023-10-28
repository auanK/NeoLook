#ifndef COMPUTER_H
#define COMPUTER_H
#include "enumerator.h"
#include "../include/queue.h"
#include "../include/min_heap.h"

template <typename Type>
class computer{
    public:
    int id;
    Type cpu;
    Type disk_1;
    Type disk_2;

    computer(priority_policy policy, id id){
        if(policy == "FCFS"){
            cpu = new queue<Type>();
            disk_1 = new queue<Type>();
            disk_2 = new queue<Type>();
        }
        else if(policy == "SJF"){
            cpu = new min_heap<Type>();
            disk_1 = new min_heap<Type>();
            disk_2 = new min_heap<Type>();
        }
        else{
            throw "Invalid policy";
        }
    }
};

#endif