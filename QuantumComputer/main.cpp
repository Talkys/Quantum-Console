#include <iostream>
#include "quantum_computer.h"
#include <fstream>
#include <chrono>
#include <omp.h>

using namespace std;

int main()
{
    //Benchmarck parameters
    int iterations   = 10000;
    int seed         = 18032024;
    bool paralelize  = true;
    int max_threads  = 8;

    //Output
    ofstream outFile("log.txt");

    //Validações pré testes
    if(!outFile)
    {
        cerr<<"Error: Unable to open output file!";
        return 1;
    }
    if(!paralelize) max_threads = 1;


    omp_set_num_threads(max_threads);
    QuantumComputer qc(seed);
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < iterations; i++)
    {
        qc.boot(10);
        qc.h(0);
        qc.h(1);
        qc.h(2);
        qc.h(3);
        qc.h(4);
        qc.h(5);
        qc.h(6);
        qc.h(7);
        qc.h(8);
        qc.h(9);

        qc.cnot(0, 1);
        qc.cnot(1, 2);
        qc.cnot(2, 3);
        qc.cnot(3, 4);
        qc.cnot(4, 5);
        qc.cnot(5, 6);
        qc.cnot(6, 7);
        qc.cnot(7, 8);
        qc.cnot(8, 9);

        qc.h(0);
        qc.h(1);
        qc.h(2);
        qc.h(3);
        qc.h(4);
        qc.h(5);
        qc.h(6);
        qc.h(7);
        qc.h(8);
        qc.h(9);

        //outFile << qc.measureQreg() << '\n';
        cout << i << " de 10" << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> time = end - start;

    cout << "\rTime for " << iterations << " iterations: " << time.count() << " seconds" << endl;

    outFile.close();

    return 0;
}
