#include "quantum_computer.h"

QuantumComputer::QuantumComputer(int seed)
{
    this->rngSeed = seed;
}

void QuantumComputer::boot(
    unsigned int qubitRegNum
    ) {

    this->qubitRegNum   = qubitRegNum;
    //this->classicRegNum = classicRegNum;
    this->amplitudes.clear();

    int n = 1 << qubitRegNum; //Macete para fazer 2 ^ qubitRegNum
    for(int i = 0; i < n; i++)
        this->amplitudes.push_back(0);
    amplitudes[0] = 1;

    this->twoBitsEntanglements.clear();
}
