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

queue<process*> readFileAndGetProcesses(const string& policy,
                                        const string& filename) {
    if (policy != "SJF" && policy != "FCFS") {
        cerr << "Política de escalonamento inválida. Use 'SJF' ou 'FCFS'."
             << endl;
        exit(1);
    }

    queue<process*> process_queue;
    FILE* file = fopen(filename.c_str(), "r");

    if (!file) {
        cerr << "Erro ao abrir o arquivo de entrada: " << filename << endl;
        exit(1);
    }

    int instant, demand_cpu, demand_disk, demand_network;
    int id = 0;
    while (fscanf(file, "%d %d %d %d", &instant, &demand_cpu, &demand_disk,
                  &demand_network) != EOF) {
        process* new_process =
            new process(id, instant, demand_cpu, demand_disk, demand_network);
        process_queue.push(new_process);
        id++;
    }

    fclose(file);

    return process_queue;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Uso: " << argv[0]
             << " <política (SJF ou FCFS)> <arquivo_de_entrada> <número_de_computadores>" << endl;
        return 1;
    }

    srand(time(NULL));

    string policy = argv[1];                   // FCFS ou SJF.
    string filename = argv[2];                 // nome do arquivo de entrada.
    int numComputers = atoi(argv[3]);          // número de computadores.

    // lê o arquivo de entrada e cria a fila de processos.
    queue<process*> process_queue = readFileAndGetProcesses(policy, "in/" + filename);

    if (policy.compare("FCFS") == 0) {
        escalonator<queue<process*>> e(numComputers, FCFS, &process_queue);
        e.run(filename);
    } else {
        escalonator<min_heap<process*>> e(numComputers, SJF, &process_queue);
        e.run(filename);
    }

    return 0;
}