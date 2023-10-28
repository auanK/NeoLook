#include <iostream>

#include "../include/queue.h"

using namespace std;

// Main para testar a implementação da fila.
int main() {
    // Criamos um vetor de inteiros e inicializamos com alguns valores.
    int v[] = {5, 3, 7, 1, 2, 9, 4, 8, 6, 0};

    // Criamos uma fila de inteiros.
    queue<int> fila;

    // Percorremos o vetor inserindo os valores na fila, imprimindo o primeiro e
    // último elemento da fila a cada inserção.
    cout << "Inserindo elementos na fila:" << endl;
    for (int i = 0; i < 10; i++) {
        fila.push(v[i]);
        cout << "Primeiro: " << fila.front() << endl;
        cout << "Último: " << fila.back() << endl;
        cout << "-----------------------" << endl;
    }

    // Imprimimos o tamanho da fila.
    cout << "Tamanho: " << fila.size() << endl;

    // Removemos os elementos da fila, imprimindo o primeiro e último elemento da
    // fila a cada remoção.
    cout << "Removendo elementos da fila:" << endl;
    while (fila.size() > 0) {
        cout << "Primeiro: " << fila.front() << endl;
        cout << "Último: " << fila.back() << endl;
        cout << "-----------------------" << endl;
        fila.pop();
    }
}