#ifndef METRICS_H
#define METRICS_H

#include <iomanip>
#include <iostream>
#include <fstream>

// Classe que armazena as métricas de execução do simulador.
class metrics {
   private:
    int total_time;          // Tempo total de execução.
    double average_time;     // Tempo médio de execução.
    double average_wait;     // Tempo médio de espera.
    double processing_rate;  // Taxa de processamento.

   public:
    // Construtor, inicializa as métricas.
    metrics(int total_time, double average_time, double average_wait, double processing_rate) {
        this->total_time = total_time;
        this->average_time = average_time;
        this->average_wait = average_wait;
        this->processing_rate = processing_rate;
    }

    // Printa as métricas.
    void print() {
        std::cout << "Tempo total: " << total_time << std::endl;
        std::cout << "Tempo médio de execução: " << std::fixed << std::setprecision(3) << average_time << std::endl;
        std::cout << "Tempo médio de espera: " << std::fixed << std::setprecision(3) << average_wait << std::endl;
        std::cout << "Taxa de processamento: " << std::fixed << std::setprecision(8) << processing_rate << std::endl;
    }

    // Salvando as métricas em um arquivo.
    void save() {
        std::ofstream file;
        file.open("metrics.txt");
        file << "Tempo total: " << total_time << std::endl;
        file << "Tempo médio de execução: " << std::fixed << std::setprecision(3) << average_time << std::endl;
        file << "Tempo médio de espera: " << std::fixed << std::setprecision(3) << average_wait << std::endl;
        file << "Taxa de processamento: " << std::fixed << std::setprecision(8) << processing_rate << std::endl;
        file.close();
    }
};

#endif