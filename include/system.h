#ifndef SYSTEM_H
#define SYSTEM_H
#include "../include/min_heap.h"
#include "../include/queue.h"

typedef enum priority_policy priority_policy;
enum priority_policy{
    FCFS,
    SJF
};

typedef enum event evento;
enum event{
    chegada_processo,
    conclusao_cpu,
    conclusao_disk,
    conclusao_rede,
    liberacao_resource
};

class processo{
    public:
    processo(int d_cpu, int d_disk, int d_rede);
    //implementar metodos p obter as demandas e avançar o processo
};

class resource{
    public:
    resource();
    void add_processo(processo* p){

    }
    processo* next_p(){
        //implementar com base na politica de escalonamento
    }
};

template <typename Type>
class computer{
    public:
    Type cpu;
    Type disk_1;
    Type disk_2;
    computer(int id);
    void atribuir_p(processo* p){
        //atribuir um processo a um recurso do computador
    }
};

template <typename T>
class escalonador{
    public:
    escalonador(priority_policy policy);
    void select_nextp(resource* recurso, queue<T>* fila); // baseado na politica de escalonamento
};

class evento{

};

class simulator{
    public:
    simulator(int qtd_computer, priority_policy policy);
    void start();
    void add_processo(processo* p); //gerar eventos p iniciar processos
    void liberar_resource(resource* r);
    void tratar_evento(evento event); //  avançar o tempo e tratar os eventos
};

#endif