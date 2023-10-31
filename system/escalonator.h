#ifndef ESCALONATOR_H
#define ESCALONATOR_H
#include "event.h"
#include "computer.h"
#include "../include/queue.h"

template <typename Type>
class escalonator{
    public:
    queue<event> events;
    computer<Type<process>>* computer;
    int size;

    escalonator(int computers){
        this->computer = new computer<Type<process>>[computers];
        this->size = computers;
    }

    void add_process(){
        srand(time(NULL));
        int index = rand() % size;

        // events.push(event(instant, type, process));
        // computer[index].add
    }

    ~escalonator(){
        delete[] computer;
    }
    
};

#endif