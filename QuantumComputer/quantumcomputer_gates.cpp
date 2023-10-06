#include "quantumcomputer.h"

void QuantumComputer::id(int offset) {
    this->qasm.push_back("id q[" + std::to_string(offset) + "];");
}

void QuantumComputer::x(int offset) {
    qasm.push_back("x q[" + std::to_string(offset) + "];");
    applySingleBitMatrix(
        offset,
        {{0, 1},
         {1, 0}}
    );
}

void QuantumComputer::y(int offset) {
    this->qasm.push_back("y q[" + std::to_string(offset) + "];");
    this->applySingleBitMatrix(
        offset,
        {{0, std::complex<double>(0, -1)},
         {std::complex<double>(0, 1), 0}}
    );
}

void QuantumComputer::z(int offset) {
    qasm.push_back("z q[" + std::to_string(offset) + "];");
    applySingleBitMatrix(
        offset,
        {{1,                                      0},
         {std::complex<double>(1, -1), std::sqrt(2)}}
    );
}

void QuantumComputer::t(int offset) {
    qasm.push_back("t q[" + std::to_string(offset) + "];");
    applySingleBitMatrix(
        offset,
        {{1,                                         0},
         {0, std::complex<double>(1, 1) / std::sqrt(2)}}
    );
}

void QuantumComputer::tdg(int offset) {
    qasm.push_back("tdg q[" + std::to_string(offset) + "];");
    applySingleBitMatrix(
        offset,
        {{1,                                         0},
         {0, std::complex<double>(1,-1) / std::sqrt(2)}}
    );
}

void QuantumComputer::s(int offset)
{
    this->qasm.push_back("s q[" + std::to_string(offset) + "];");
    this->applySingleBitMatrix(
        offset,
        {{1,                          0},
         {0, std::complex<double>(0, 1)}}
    );
}

void QuantumComputer::sdg(int offset)
{
    this->qasm.push_back("sdg q[" + std::to_string(offset) + "];");
    this->applySingleBitMatrix(
        offset,
        {{1,                          0},
         {0, std::complex<double>(0,-1)}}
    );
}

void QuantumComputer::h(int offset)
{
    this->qasm.push_back("h q[" + std::to_string(offset) + "];");
    const std::complex<double> t = (1 / std::sqrt(2));
    this->applySingleBitMatrix(
        offset,
        {{t, t},
         {t,-t}}
    );
}

void QuantumComputer::cnot(int control, int target)
{
    this->qasm.push_back(
    "cx q["+std::to_string(control)+"],q["+std::to_string(target)+"];"
    );
    this->applyTwoBitsMatrix(
        control, target,
        {{1, 0, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 1},
         {0, 0, 1, 0}}
    );
}
