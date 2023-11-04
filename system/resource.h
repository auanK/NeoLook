#ifndef RESOURCE_H
#define RESOURCE_H

#include "../include/min_heap.h"
#include "../include/queue.h"
#include "computer.h"
#include "enumerator.h"
#include "process.h"

template <typename type>
class resource {
   private:
    computer<type> *computer_type;
    type *network;
    int amount;
    priority_policy policy;

   public:
    resource(int amount, priority_policy policy) {
        this->amount = amount;
        this->policy = policy;
        this->computer_type = new computer<type>[amount];
        this->network = new type();

        if (policy == SJF) {
            for (int i = 0; i < amount; i++) {
                if constexpr (std::is_same_v<type, min_heap<process *>>) {
                    this->computer_type[i].cpu->set_comparator(
                        &compare_process_cpu);
                    this->computer_type[i].disk_1->set_comparator(
                        &compare_process_disk);
                    this->computer_type[i].disk_2->set_comparator(
                        &compare_process_disk);
                }
            }
            if constexpr (std::is_same_v<type, min_heap<process *>>) {
                this->network->set_comparator(&compare_process_network);
            }
        }
    }

    void add_process(process *process) {
        int random_index = rand() % amount;
        computer_type[random_index].add_process_cpu(process);
        std::cout << process << " adicionado na CPU " << random_index
                  << std::endl
                  << std::endl;
        computer_type[random_index].print();
        std::cout << std::endl;
    }

    ~resource() {
        delete[] computer_type;
        delete network;
    }
};

#endif
