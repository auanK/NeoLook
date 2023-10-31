#ifndef EVENT_H
#define EVENT_H
#include "enumerator.h"
#include "process.h"

class event{
    int instant;
    type_event type;
    process* processo;
};

#endif