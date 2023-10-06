#ifndef QUANTUMCOMPUTER_H
#define QUANTUMCOMPUTER_H

#include <vector>
#include <string>
#include <map>
#include <complex>
#include <random>
#include <iostream>
#include <unordered_map>

template <typename T>
using Matrix = std::vector<std::vector<T>>;

class QuantumComputer
{
private:
    std::vector<std::string>          qasm;
    unsigned int                      qubitRegNum;
    unsigned int                      classicRegNum;
    std::map<int, int>                twoBitsEntanglements;
    std::vector<std::complex<double>> amplitudes;
    std::vector<int>                  measures;
    int                               rngSeed;

    Matrix<std::complex<double>> multiply(
        const Matrix<std::complex<double>>& A,
        const Matrix<std::complex<double>>& B
    );

public:
    QuantumComputer(int);

    void boot(unsigned int, unsigned int = -1);

    Matrix<std::pair<int, std::complex<double>>>
    getSingleQubitPairs(unsigned int);

    Matrix<std::pair<int, std::complex<double>>>
    getTwoQubitsPairs(int, int);

    std::vector<double> getQubitProbability(int offset);

    double getQubitsProbability(
        const std::vector<int>& offsets,
        const std::vector<int>& targets
    );

    void applySingleBitMatrix(
        int offset,
        const Matrix<std::complex<double>>& matrix
    );

    void applyTwoBitsMatrix(
        int control,
        int target,
        const Matrix<std::complex<double>>& matrix
    );

    void id(int offset);

    void x(int offset);

    void y(int offset);

    void z(int offset);

    void t(int offset);

    void tdg(int offset);

    void s(int offset);

    void sdg(int offset);

    void h(int offset);

    void cnot(int control, int target);

    std::vector<std::string> amplitudes_to_string();

    int measureQreg();

    int fakemeasure(int);
};

#endif // QUANTUMCOMPUTER_H
