#ifndef RESOURCES_H
#define RESOURCES_H
#include "enumerator.h"
#include <vector>

template <typename Type>
class resources{
    public:
    int n;
    Type computador;
    Type network;

    resources(int n, priority_policy policy){
        this->n = n;
        if(policy == "FCFS"){
            network = new queue<Type>();
        }
        else if(policy == "SJF"){
            network = new min_heap<Type>();
        }
        else{
            throw "Invalid policy";
        }

        //cria um vetor de computadores com id's de 0 a n-1;
        std::vector<computer<Type>> computadores;
        for(int i = 0; i < n; i++){
            computadores.push(new computer<Type>(policy, i));
        }
        
    }

    

    
};
#endif