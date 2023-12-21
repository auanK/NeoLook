#include <time.h>

#include <iostream>
#include <string>
#include <vector>

#include "../include/min_heap.h"
#include "../include/queue.h"
#include "../system/computer.h"
#include "../system/enumerator.h"
#include "../system/escalonator.h"
#include "../system/process.h"
#include "../system/resource.h"

using namespace std;

// Método que lê o arquivo de entrada e retorna uma fila de processos.
queue<process*> readFileAndGetProcesses(const string& policy, const string& filename) {
    // Verifica se a política de escalonamento é válida.
    if (policy != "SJF" && policy != "FCFS") {
        cerr << "Política de escalonamento inválida. Use 'SJF' ou 'FCFS'." << endl;
        throw invalid_argument("Política de escalonamento inválida.");
    }

    // Cria a fila de processos.
    queue<process*> process_queue;
    // Abre o arquivo de entrada.
    ifstream file(filename);

    // Verifica se o arquivo foi aberto corretamente.
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        throw invalid_argument("Erro ao abrir o arquivo de entrada.");
    }
    // Lê o arquivo de entrada e cria os processos.
    int instant, demand_cpu, demand_disk, demand_network;
    int id = 0;
    while (file >> instant >> demand_cpu >> demand_disk >> demand_network) {
        // Cria o processo.
        process* p = new process(id++, instant, demand_cpu, demand_disk, demand_network);
        // Adiciona o processo na fila.
        process_queue.push(p);
    }

    // Fecha o arquivo de entrada.
    file.close();

    // Retorna a fila de processos.
    return process_queue;
}

// Classe main.
int main(int argc, char* argv[]) {
    // Verifica se o número de argumentos é válido.
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <política (SJF ou FCFS)> <arquivo_de_entrada> <número_de_computadores>" << endl;
        return 1;
    }

    // Inicializa a semente do gerador de números aleatórios.
    srand(time(NULL));
    //srand(123); // Usada para debug.

    string policy = argv[1];                   // política de escalonamento.
    string filename = argv[2];                 // nome do arquivo de entrada.
    int numComputers = atoi(argv[3]);          // número de computadores.

    // lê o arquivo de entrada e cria a fila de processos.
    queue<process*> process_queue = readFileAndGetProcesses(policy, "src/in/" + filename);

    // Verifica qual a política de escalonamento selecionada.
    if (policy.compare("FCFS") == 0) {
        // Cria o escalonador com a política FCFS.
        escalonator<queue<process*>> e(numComputers, FCFS, &process_queue);
        // Executa o escalonador.
        e.run(filename);
    } else {
        // Cria o escalonador com a política SJF.
        escalonator<min_heap<process*>> e(numComputers, SJF, &process_queue);
        // Executa o escalonador.
        e.run(filename);
    }

    return 0;
}