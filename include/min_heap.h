#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#include <stdexcept>
#include <iostream>
using namespace std;
// seja h uma lista, h.size o tamanho da lista, temos que para um elemento i
// seus filhos serao 2i + 1 e 2i + 2 e seu pai sera (i - 1)/2

//comparator
bool is_bigger(int a, int b){
   return a > b;
}

class min_heap{
    private:
    int size;
    int capacity;
    int *ptr;

// função que compara pai e filho e troca caso pai>filho
    void up(int index){
        if(index > 0){
            int daddy = (index - 1)/2;
            if(is_bigger(ptr[daddy], ptr[index])){
                swap(&ptr[daddy], &ptr[index]);
                up(daddy);
            }
        }
    }

//função que compara menor filho e pai e troca caso pai>menor filho
    void down(int index){
        int index_smaller = (index * 2) + 1;

        if(index_smaller < this->size){
            if((index_smaller + 1) < this->size){
                if(is_bigger(ptr[index_smaller], ptr[index_smaller + 1])){
                    index_smaller += 1;
                }
            }
            if(is_bigger(ptr[index], ptr[index_smaller])){
                swap(&ptr[index], &ptr[index_smaller]);
                down(index_smaller);
            }
        }
    }
//inicialização
    public:
    min_heap(){
        this->size = 0;
        this->capacity = 1;
        this->ptr = new int;
    }
    //encapsulamento
    int get_size(){
        return this->size;
    }
    int get_capacity(){
        return this->capacity;
    }
    //destrutor
    ~min_heap(){
        delete[] ptr;
    }
    //função de troca
    void swap(int *a, int *b){
        int aux = *a;
        *a = *b;
        *b = aux;
    }
    //função que adiciona elemento e chama a função up para ordenar o heap
    void push(int value){
        this->print();
        ptr[size] = value;
        size++;

        if(size == capacity){
            int *aux = new int[capacity*2];
            for(int i = 0; i < size; i++){
                aux[i] = ptr[i];
            }
            delete[] ptr;
            ptr = aux;
            capacity = capacity*2;
        }

        up(size-1);
    }
    //função que remove elemento e chama a função down para ordenar o heap
    int pop(){
        if(size == 0){
            throw 0;
        }
        this->print();

        int aux = ptr[0];

        swap(&ptr[0], &ptr[size-1]);
        size--;
        down(0);

        return aux;
    }
    //função p/ imprimir
    void print(){
        for(int i = 0; i < size; i++){
            cout << ptr[i] << " ";
        }
        cout << endl;
    }
};




#endif