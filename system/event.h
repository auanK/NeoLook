#ifndef EVENT_H
#define EVENT_H
#include "enumerator.h"
#include "process.h"

class event{
    public:
    int instant;
    type_event type;
    process* processo;

    event(int instant, type_event event, process* p){
        this->instant = instant;
        this->type = event;
        this->processo = p;
    }
};

#endif