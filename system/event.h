#ifndef EVENT_H
#define EVENT_H
#include "enumerator.h"
#include "process.h"

// Classe que armazena os eventos do simulador.
class event {
   public:
    int instant;         // Instante em que o evento ocorre.
    type_event type;     // Tipo do evento.
    process* process_a;  // Processo associado ao evento.

    // Construtor, inicializa os atributos.
    event(int instant, type_event event, process* p) {
        this->instant = instant;
        this->type = event;
        this->process_a = p;
    }

    // Destrutor, deleta o processo.
    ~event() { 
        delete process_a; 
    }

    // Printa o evento. (Utilizado para debug)
    void print() {
        switch (type) {
            case INITIALIZE_PROCESS:
                std::cout << "INITIALIZE_PROCESS" << std::endl;
                break;
            case WAIT_CPU:
                std::cout << "WAIT_CPU" << std::endl;
                break;
            case ACCESS_CPU:
                std::cout << "ACCESS_CPU" << std::endl;
                break;
            case WAIT_DISK:
                std::cout << "WAIT_DISK" << std::endl;
                break;
            case ACCESS_DISK:
                std::cout << "ACCESS_DISK" << std::endl;
                break;
            case WAIT_NETWORK:
                std::cout << "WAIT_NETWORK" << std::endl;
                break;
            case ACCESS_NETWORK:
                std::cout << "ACCESS_NETWORK" << std::endl;
                break;
            case FINISH_PROCESS:
                std::cout << "FINISH_PROCESS" << endl;
                break;
        }

        std::cout << "ID: " << process_a->id << std::endl;
        std::cout << "Instant: " << instant << std::endl;
        std::cout << "Demand CPU: " << process_a->demand_cpu << std::endl;
        std::cout << "Demand Disk: " << process_a->demand_disk << std::endl;
        std::cout << "Demand Network: " << process_a->demand_network << std::endl;
    }
};

#endif