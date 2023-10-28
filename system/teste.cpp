#include <iostream>

#include "../include/min_heap.h"
#include "../include/queue.h"
#include "computer.h"
#include "enumerator.h"
#include "process.h"

using namespace std;

int main() {
    computer<min_heap<int>> computer;

    process p1(1, 3, 4, 5);
    computer.add_process(p1);

    process p2(2, 2, 3, 4);
    computer.add_process(p2);

    computer.print();
}
