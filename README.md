# NeoLook 
 
Trabalho da cadeira Estrutura de Dados, do curso de Ciência da Computação da UFC - Campus Quixada, lecionada pelo professor Atílio Gomes Luiz, no semestre 2023.2, Realizado pelos alunos [Kauan Pablo](https://github.com/auanK) e [Erica de Castro](https://github.com/erymustdie).

## Descrição do Projeto
O trabalho consiste em criar um sistema chamado NeoLook que tem como objetivo simular a execução de uma série de processos de acordo com a política de escalonamento FCFS ou SJF e a partir disso, gerar métricas de desempenho do sistema. O sistema foi desenvolvido em C++ e para mais informações do projeto, leia o relatório do projeto na pasta docs.

## Como executar o projeto
Execute o seguinte comando para compilar o projeto:
```bash
g++ src/main.cpp -o main
```

Em seguida:
```bash
./main <política (SJF ou FCFS)> <arquivo_de_entrada> <número_de_computadores>
```

Onde o arquivo_de_entrada deve está na pasta src/in. 

Ao final da execução será gerado um arquivo de saída na pasta src/out com as métricas do sistema.

## Observações
O relatório do sistema pode ter algumas informações modificadas pois o sistema foi atualizado após a entrega do relatório, mas o funcionamento do sistema e as explicações do código são as mesmas pois apenas alguns métodos foram refatorados.