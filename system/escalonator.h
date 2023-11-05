#ifndef ESCALONATOR_H
#define ESCALONATOR_H

#include "../include/queue.h"
#include "computer.h"
#include "enumerator.h"
#include "event.h"
#include "metrics.h"
#include "resource.h"

template <typename Type>
class escalonator {
   public:
    queue<event*> events;            // Fila de eventos
    resource<Type>* system;          // Sistema(um recurso)
    queue<process*>* process_queue;  // Fila de processos

    // Vetor de ponteiros para eventos (serao registrados 8 eventos por
    // processo)
    event** events_vec;
    int size_events;  // Tamanho do vetor de eventos
    int qtd_process;  // Quantidade de processos

    // Matriz de ponteiros para eventos, cada linha eh dedicada a um processo
    // possuindo todos os eventos relacionados a ele.
    event*** log;

    // Construtor (recebe a quantidade de computadores, a politica de
    // escalonamento e a fila de processos a serem processados).
    escalonator(int amount, priority_policy p, queue<process*>* process_queue) {
        this->system = new resource<Type>(amount, p);  // Inicializando o sistema
        this->process_queue =
            process_queue;  // Inicializando a fila de processos
        qtd_process =
            process_queue->size();  // Inicializando a quantidade de processos

        // Cada processo sera registrado em 8 eventos:
        //      -> Iniciar processo.
        //      -> Esperar CPU
        //      -> Acessar CPU
        //      -> Esperar Disco
        //      -> Acessar Disco
        //      -> Esperar Rede
        //      -> Acessar Rede
        //      -> Terminar Processo

        // O vetor de eventos tera o tamanho de 8 vezes a quantidade de
        // processos.
        events_vec = new event*[qtd_process * 8];

        // Inicializando o tamanho do vetor de eventos.
        size_events = 0;

        // Inicializando a matriz de eventos.
        log = new event**[qtd_process];

        // Inicializando cada linha da matriz de eventos.
        for (int i = 0; i < qtd_process; i++) {
            log[i] = new event*[8];
        }
    }

    // Metodo que executa o escalonamento.
    void run() {
        int time = 0;  // Instante de tempo

        // Loop que executa o escalonamento.
        while (true) {
            bool has_process_in_system = false;  // Flag que indica se ha processo no sistema.

            // Verificando se ha processo a ser processado no sistema.
            for (int i = 0; i < this->system->amount; i++) {
                // Se houver processo no sistema, a flag eh setada para true e o
                // loop eh quebrado.
                if (this->system->computer_type[i].has_process()) {
                    has_process_in_system = true;
                    break;
                }
            }

            // Se nao houver processo na fila de processos, no sistema e na
            // rede, o escalonamento eh finalizado.
            if (process_queue->empty() &&
                !this->system->has_process_in_network() &&
                !has_process_in_system) {
                break;
            }

            // Enquanto houver processo na fila de processos e o instante de
            // tempo for igual ao instante de chegada do processo, o processo eh
            // adicionado ao sistema.
            while (!process_queue->empty() && process_queue->front()->instant == time) {
                process* p = process_queue->pop();  // Retirando o processo da fila de processos.

                // Registrando o evento de inicializacao do processo.
                events_vec[size_events] = (new event
                    (time, INITIALIZE_PROCESS, new process(p->id, p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                // Incrementando o tamanho do vetor de eventos.
                size_events++;

                // Registrando o evento de espera da CPU.
                events_vec[size_events] = (new event
                    (time, WAIT_CPU, new process(p->id, p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                // Incrementando o tamanho do vetor de eventos.
                size_events++; 
                
                // Adicionando o processo ao sistema.
                system->add_process(p);
            }

            // Percorrendo cada computador do sistema.
            for (int i = 0; i < system->amount; i++) {
                // Criando um ponteiro para o computador atual.
                computer<Type>* pc = &this->system->computer_type[i];

                // PROCESS_CPU
                // Verificando se nao existe processo em execucao na CPU.
                if (!pc->has_process_in_cpu()) {
                    // Retirando o processo da fila de espera da CPU.
                    process* p = pc->cpu->pop();

                    // Verificando se existe processo na fila de espera da CPU.
                    if (p != nullptr) {
                        // Se existir, o processo eh adicionado a execucao da CPU.
                        pc->running_cpu = p;

                        // Registrando o evento de acesso a CPU.
                        events_vec[size_events] = (new event
                        (time, ACCESS_CPU, new process(p->id, p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                        // Incrementando o tamanho do vetor de eventos.
                        size_events++;
                    }
                } else {
                    // Se existir processo em execucao na CPU, a demanda de CPU do processo eh decrementada.
                    pc->consume_cpu();

                    // Caso a demanda de CPU do processo seja igual a 0, o processo eh retirado da execucao da CPU.
                    if (pc->running_cpu->demand_cpu == 0) {
                        // Salvando o processo em execucao na CPU.
                        process* p = pc->running_cpu;

                        // Registrando o evento de espera do disco.
                        events_vec[size_events] = (new event
                        (time, WAIT_DISK, new process(p->id, p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                        // Incrementando o tamanho do vetor de eventos.
                        size_events++;

                        // Adiciona o processo na fila de espera de um dos discos.
                        pc->add_process_disk();

                        // Retirando o processo da execucao da CPU.
                        pc->running_cpu = nullptr;
                    }
                }

                // PROCESS_DISK_1
                // Verificando se nao existe processo em execucao no disco 1.
                if (!pc->has_process_in_disk_1()) {
                    // Retirando o processo da fila de espera do disco 1.
                    process* p = pc->disk_1->pop();

                    // Verificando se existe processo na fila de espera do disco 1.
                    if (p != nullptr) {
                        // Adicionando o processo a execucao do disco 1.
                        pc->running_disk_1 = p;

                        // Registrando o evento de acesso ao disco.
                        events_vec[size_events] = (new event
                            (time, ACCESS_DISK, new process(p->id, p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                        // Incrementando o tamanho do vetor de eventos.
                        size_events++;
                    }
                } else {
                    // Se existir processo em execucao no disco 1, a demanda de disco do processo eh decrementada.
                    pc->running_disk_1->demand_disk--;
                }

                // PROCESS_DISK_2
                // Verificando se nao existe processo em execucao no disco 2.
                if (!pc->has_process_in_disk_2()) {
                    // Retirando o processo da fila de espera do disco 2.
                    process* p = pc->disk_2->pop();

                    // Verificando se existe processo na fila de espera do disco 2.
                    if (p != nullptr) {
                        // Adicionando o processo a execucao do disco 2.
                        pc->running_disk_2 = p;

                        // Registrando o evento de acesso ao disco.
                        events_vec[size_events] = (new event
                        (time, ACCESS_DISK, new process(p->id, p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                        // Incrementando o tamanho do vetor de eventos.
                        size_events++;
                    }
                } else {
                    // Se existir processo em execucao no disco 2, a demanda de disco do processo eh decrementada.
                    pc->running_disk_2->demand_disk--;
                }

                // CONSUME_DISK
                process* disk1_p = pc->running_disk_1;  // Processo em execucao no disco 1.

                // Verificando se o processo em execucao no disco 1 terminou.
                if (pc->has_process_in_disk_1() && disk1_p->demand_disk == 0) {
                    // Salvando o processo em execucao no disco 1.
                    process* p = disk1_p;
                    // Retirando o processo da execucao do disco 1.
                    pc->running_disk_1 = nullptr;

                    // Registrando o evento de espera da rede.
                    events_vec[size_events] = (new event
                        (time, WAIT_NETWORK, new process(p->id, p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                    // Incrementando o tamanho do vetor de eventos.
                    size_events++;

                    // Adicionando o processo a fila de espera da rede.
                    this->system->network->push(p);
                }

                process* disk2_p = pc->running_disk_2;  // Processo em execucao no disco 2.

                // Verificando se o processo em execucao no disco 2 terminou.
                if (pc->has_process_in_disk_2() && disk2_p->demand_disk == 0) {
                    // Salvando o processo em execucao no disco 2.
                    process* p = disk2_p;
                    // Retirando o processo da execucao do disco 2.
                    pc->running_disk_2 = nullptr;

                    // Registrando o evento de espera da rede.
                    events_vec[size_events] = (new event
                         (time, WAIT_NETWORK, new process(p->id, p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));
                    
                    // Incrementando o tamanho do vetor de eventos.
                    size_events++;

                    // Adicionando o processo a fila de espera da rede.
                    this->system->network->push(p);
                }

                // PROCESS_NETWORK

                // Verificando se nao existe processo em execucao na rede.
                if (this->system->running_network == nullptr) {
                    // Retirando o processo da fila de espera da rede.
                    process* p = this->system->network->pop();

                    // Verificando se existe processo na fila de espera da rede.
                    if (p != nullptr) {
                        // Adicionando o processo a execucao da rede.
                        this->system->running_network = p;

                        // Registrando o evento de acesso a rede.
                        events_vec[size_events] = (new event
                            (time, ACCESS_NETWORK, new process(p->id, p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                        // Incrementando o tamanho do vetor de eventos.
                        size_events++;
                    }
                } else {
                    // Se existir processo em execucao na rede, a demanda de rede do processo eh decrementada.
                    this->system->running_network->demand_network--;
                }

                // CONSUME_NETWORK
                // Verificando se o processo em execucao na rede terminou.
                if (this->system->running_network != nullptr &&
                    this->system->running_network->demand_network == 0) {

                    // Salvando o processo em execucao na rede.
                    process* p = this->system->running_network;
                    // Retirando o processo da execucao da rede.
                    this->system->running_network = nullptr;

                    // Registrando o evento de termino do processo.
                    events_vec[size_events] = (new event
                    (time, FINISH_PROCESS, new process(p->id, p->instant, p->demand_cpu, p->demand_disk, p->demand_network)));

                    // Incrementando o tamanho do vetor de eventos.
                    size_events++;

                    // Deletando o processo. (Lembrando que os eventos guardam uma copia do processo, 
                    // entao nao ha problema em deletar o processo aqui)
                    delete p;
                }
            }
            // Incrementando o instante de tempo.
            time++;
        }

        // Cria uma fila de eventos para cada processo(8 eventos por processo)
        for (int i = 0; i < (qtd_process * 8); i++) {
            events.push(events_vec[i]);
        }

        // Contador de eventos registrados para cada processo
        int* counter_event = new int[qtd_process];

        // inicializando contadores
        for (int i = 0; i < qtd_process; i++) {
            counter_event[i] = 0;
        }

        // Cada evento eh colocado em sua devida linha de processo de acordo com
        // o ID do processo, os eventos de cada processo serao colocados em ordem
        // cronologica.
        for (int i = 0; i < (qtd_process * 8); i++) {
            // Retirando o evento da fila de eventos.
            event* e = events.pop();
            // Registrando o evento na matriz de eventos.
            log[e->processo->id][counter_event[e->processo->id]] = e;
            // Incrementando o contador de eventos do processo.
            counter_event[e->processo->id]++;
        }

        // Deletando o vetor de contadores de eventos.
        delete[] counter_event;

        // Calculando as metricas.

        // Tempo medio de resposta = (tempo de espera + tempo de execucao) / numero de processos
        double average_time = 0;

        // Tempo medio de espera = tempo de espera / numero de processos
        double average_wait = 0;

        // Taxa de processamento = numero de processos / termino do ultimo processo - inicio do primeiro processo
        double processing_rate = static_cast<double> (qtd_process) / ((time - 1) - log[0][0]->instant);

        // Percorrendo cada processo.
        for (int i = 0; i < qtd_process; i++) {
            double demand_cpu = log[i][0]->processo->demand_cpu;            // Demanda da CPU de quando o processo foi inicializado.
            double demand_disk = log[i][0]->processo->demand_disk;          // Demanda do disco de quando o processo foi inicializado.
            double demand_network = log[i][0]->processo->demand_network;    // Demanda da rede de quando o processo foi inicializado.

            double wait_cpu = log[i][2]->instant - log[i][1]->instant;      // Tempo de espera na CPU. (instante de acesso a CPU - instante de espera da CPU)
            double wait_disk = log[i][4]->instant - log[i][3]->instant;     // Tempo de espera no disco. (instante de acesso ao disco - instante de espera do disco)
            double wait_network = log[i][6]->instant - log[i][5]->instant;  // Tempo de espera na rede. (instante de acesso a rede - instante de espera da rede)

            // Tempo de execucao = tempo de espera geral + demanda geral
            average_time += (wait_cpu + wait_disk + wait_network + demand_cpu + demand_disk + demand_network);

            // Tempo de espera = tempo de espera na CPU + tempo de espera no disco + tempo de espera na rede
            average_wait += (wait_cpu + wait_disk + wait_network);
        }
        // Tempo medio de execucao = tempo medio de execucao / numero de processos
        average_time /= qtd_process;
        // Tempo medio de espera = tempo medio de espera / numero de processos
        average_wait /= qtd_process;

        // Criando um objeto de metricas.
        metrics m(time, average_time, average_wait, processing_rate);

        // Imprimindo as metricas.
        m.print();
        //m.save();
    }

    // Destrutor, desaloca os eventos, o sistema e a matriz de eventos.
    ~escalonator() {
        // Deletando a fila de eventos.
        while (!events.empty()) {
            event* e = events.pop();
            delete e;
        }

        // Deletando o sistema.
        delete system;

        for (int i = 0; i < size_events; i++) {
            delete events_vec[i];
        }

        delete[] events_vec;

        // Deletando cada linha da matriz de eventos.
        for (int i = 0; i < qtd_process; i++) {
            delete[] log[i];
        }

        // Deletando a matriz de eventos.
        delete[] log;
    }
};

#endif