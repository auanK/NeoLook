#include <iostream>

#include "../include/min_heap.h"

using namespace std;

// Main para testar a implementação da min_heap.
int main() {
    // Criamos um vetor de inteiros e inicializamos com alguns valores em
    // desordem.
    int v[] = {5, 3, 7, 1, 2, 9, 4, 8, 6, 0};

    // Criamos uma min_heap de inteiros.
    min_heap<int> heap;

    // Percorremos o vetor inserindo os valores na min_heap e imprimimos
    // o estado da heap a cada inserção.
    cout << "Inserindo elementos na heap:" << endl;
    for (int i = 0; i < 10; i++) {
        heap.push(v[i]);
        heap.printTree(0);
        cout << "-----------------------" << endl;
    }

    // Imprimimos o vetor de inteiros.
    cout << "Vetor: ";
    heap.print();

    // Imprimimos o tamanho e a capacidade da heap.
    cout << "Tamanho: " << heap.size() << endl;
    cout << "Capacidade: " << heap.capacity() << endl;

    // Imprimimos o elemento da raiz da heap.
    cout << "Raiz: " << heap.root() << endl;
    cout << "-----------------------" << endl;

    // Removemos o elemento da raiz da heap e imprimimos o estado da heap a cada
    // remoção.
    cout << "Removendo elementos da heap:" << endl;
    while (heap.size() > 0) {
        heap.printTree(0);
        cout << "-----------------------" << endl;
        heap.pop();
    }
}