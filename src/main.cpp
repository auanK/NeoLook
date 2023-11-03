#include <iostream>
#include <string>
#include <vector>

#include "../include/min_heap.h"
#include "../include/queue.h"
#include "../system/computer.h"
#include "../system/process.h"
#include "../system/resource.h"
#include "../system/enumerator.h"

using namespace std;

vector<process*> readFileAndGetProcesses(const string& policy,
                                         const string& filename) {
    if (policy != "SJF" && policy != "FCFS") {
        cerr << "Política de escalonamento inválida. Use 'SJF' ou 'FCFS'."
             << endl;
        exit(1);
    }

    vector<process*> process_vector;
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
        process_vector.push_back(new_process);
    }

    fclose(file);

    return process_vector;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0]
             << " <política (SJF ou FCFS)> <arquivo de entrada>" << endl;
        return 1;
    }

    string policy = argv[1];
    string filename = argv[2];

    vector<process*> process_vector = readFileAndGetProcesses(policy, filename);

    if (policy == "SJF") {
        priority_policy policy_enum = SJF;
        cout << "Executando política SJF..." << endl;
        resource<min_heap<process*> > resource(2, policy_enum);
    } else if (policy == "FCFS") {
        priority_policy policy_enum = FCFS;
        cout << "Executando política FCFS..." << endl;
        resource<queue<process*> > resource(2, policy_enum);
    }


    int time = 0;
    while (true) {
        if (process_vector.size() == 0) {
            break;
        }
        process_vector.erase(process_vector.begin());
        time++;
    }

    return 0;
}
