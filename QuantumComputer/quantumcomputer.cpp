#include "quantumcomputer.h"

QuantumComputer::QuantumComputer(int seed)
{
    this->rngSeed = seed;
}

void QuantumComputer::boot(
        unsigned int qubitRegNum,
        unsigned int classicRegNum
) {
    if(classicRegNum == -1) classicRegNum = qubitRegNum;
    this->qasm.push_back("qreg q[" + std::to_string(qubitRegNum) + "];");
    this->qasm.push_back("creg c[" + std::to_string(classicRegNum) + "];");

    this->qubitRegNum   = qubitRegNum;
    this->classicRegNum = classicRegNum;
    this->amplitudes.clear();

    int n = 1 << qubitRegNum; //Macete para fazer 2 ^ qubitRegNum
    for(int i = 0; i < n; i++)
        this->amplitudes.push_back(0);
    amplitudes[0] = 1;

    this->measures.clear();
    for(int i = 0; i < classicRegNum; i++)
        measures.push_back(-1);

    this->twoBitsEntanglements.clear();
}
