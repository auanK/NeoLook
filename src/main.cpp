#include <time.h>

#include <iostream>
#include <string>
#include <vector>

#include "../include/min_heap.h"
#include "../include/queue.h"
#include "../system/computer.h"
#include "../system/enumerator.h"
#include "../system/process.h"
#include "../system/resource.h"
#include "../system/escalonator.h"

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
    while (fscanf(file, "%d %d %d %d", &instant, &demand_cpu, &demand_disk,
                  &demand_network) != EOF) {
        process* new_process =
            new process(instant, demand_cpu, demand_disk, demand_network);
        process_queue.push(new_process);
    }

    fclose(file);

    return process_queue;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0]
             << " <política (SJF ou FCFS)> <arquivo de entrada>" << endl;
        return 1;
    }

    srand(time(NULL));

    string policy = argv[1];
    string filename = argv[2];

    queue<process*> process_queue = readFileAndGetProcesses(policy, filename);

    if(policy.compare("FCFS")){
        escalonator<queue<process*>> e(4, FCFS, &process_queue);
        e.run();
    }else{
        escalonator<min_heap<process*>> e(4, SJF, &process_queue);
        e.run();
    }



    return 0;
}
