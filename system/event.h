#ifndef EVENT_H
#define EVENT_H
#include "enumerator.h"
#include "process.h"

// Classe que armazena os eventos do simulador.
class event {
   public:
    int instant;        // Instante em que o evento ocorre.
    type_event type;    // Tipo do evento.
    process* processo;  // Processo associado ao evento.

    // Construtor, inicializa os atributos.
    event(int instant, type_event event, process* p) {
        this->instant = instant;
        this->type = event;
        this->processo = p;
    }

    // Destrutor, deleta o processo.
    ~event() { 
        delete processo; 
    }

    // Printa o evento. (Utilizado para debug)
    void print() {
        switch (type) {
            case INITIALIZE_PROCESS:
                printf("INITIALIZE_PROCESS\n");
                break;
            case WAIT_CPU:
                printf("WAIT_CPU\n");
                break;
            case ACCESS_CPU:
                printf("ACCESS_CPU\n");
                break;
            case WAIT_DISK:
                printf("WAIT_DISK\n");
                break;
            case ACCESS_DISK:
                printf("ACCESS_DISK\n");
                break;
            case WAIT_NETWORK:
                printf("WAIT_NETWORK\n");
                break;
            case ACCESS_NETWORK:
                printf("ACCESS_NETWORK\n");
                break;
            case FINISH_PROCESS:
                printf("FINISH_PROCESS\n");
                break;
        }

        printf("ID:             %d\n", processo->id);
        printf("time:           %d\n", instant);
        printf("inicio:         %d\n", processo->instant);
        printf("demand_cpu:     %d\n", processo->demand_cpu);
        printf("demand_disk:    %d\n", processo->demand_disk);
        printf("demand_network: %d\n", processo->demand_network);
    }
};

#endif