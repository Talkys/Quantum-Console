#include "quantumcomputer.h"

void QuantumComputer::id(int offset) {
    return;
}

void QuantumComputer::x(int offset) {
    applySingleBitMatrix(
        offset,
        {{0, 1},
         {1, 0}}
    );
}

void QuantumComputer::y(int offset) {
    this->applySingleBitMatrix(
        offset,
        {{0, std::complex<double>(0, -1)},
         {std::complex<double>(0, 1), 0}}
    );
}

void QuantumComputer::z(int offset) {
    applySingleBitMatrix(
        offset,
        {{1,                                      0},
         {std::complex<double>(1, -1), std::sqrt(2)}}
    );
}

void QuantumComputer::t(int offset) {
    applySingleBitMatrix(
        offset,
        {{1,                                         0},
         {0, std::complex<double>(1, 1) / std::sqrt(2)}}
    );
}

void QuantumComputer::tdg(int offset) {
    applySingleBitMatrix(
        offset,
        {{1,                                         0},
         {0, std::complex<double>(1,-1) / std::sqrt(2)}}
    );
}

void QuantumComputer::s(int offset)
{
    this->applySingleBitMatrix(
        offset,
        {{1,                          0},
         {0, std::complex<double>(0, 1)}}
    );
}

void QuantumComputer::sdg(int offset)
{
    this->applySingleBitMatrix(
        offset,
        {{1,                          0},
         {0, std::complex<double>(0,-1)}}
    );
}

void QuantumComputer::h(int offset)
{
    const std::complex<double> t = (1 / std::sqrt(2));
    this->applySingleBitMatrix(
        offset,
        {{t, t},
         {t,-t}}
    );
}

void QuantumComputer::cnot(int control, int target)
{
    this->applyTwoBitsMatrix(
        control, target,
        {{1, 0, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 1},
         {0, 0, 1, 0}}
    );
}
