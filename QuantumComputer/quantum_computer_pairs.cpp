#include "quantum_computer.h"


template <typename T>
using Matrix = std::vector<std::vector<T>>;

Matrix<std::pair<int, std::complex<double>>>
QuantumComputer::getSingleQubitPairs(unsigned int offset)
{
    if(offset >= this->qubitRegNum)
        throw std::invalid_argument(
            "Erro: offset invalido"
            );

    std::unordered_map<int, bool> memory;
    Matrix<std::pair<int, std::complex<double>>> pairs;

    int shift = 1 << offset;

    long int amplitudes_size = this->amplitudes.size();

    for(long int i = 0; i < amplitudes_size; i++)
    {
        bool abort;
        #pragma omp critical
        {abort = (memory.find(i) != memory.end());}

        if(abort) continue;

        int n = i / shift;
        // Como os grupos são separados pelo valor do qubit
        // aqui verificamos se ele é 1 ou não aí podemos separar
        bool isOne = n % 2 == 1;
        int a = -1, b = -1;

        if(isOne) {
            a = i - shift;
            b = i;
        } else {
            a = i;
            b = i + shift;
        }

        memory[a], memory[b] = true;
        pairs.push_back({
        {a, this->amplitudes[a]},
        {b, this->amplitudes[b]}
        });
    }

    return pairs;
}

Matrix<std::pair<int, std::complex<double>>>
QuantumComputer::getTwoQubitsPairs(int control, int target)
{
    if (control >= this->qubitRegNum)
        throw std::invalid_argument(
            "Erro: Offset inválido " + std::to_string(control)
            );
    if (target >= this->qubitRegNum)
        throw std::invalid_argument(
            "Erro: Offset inválido " + std::to_string(target)
            );

    std::unordered_map<int, bool> memory;
    Matrix<std::pair<int, std::complex<double>>> pairs;
    int shiftControl = 1 << control;
    int shiftTarget = 1 << target;


    int amplitudes_size = this->amplitudes.size();

    for(int i = 0; i < amplitudes_size; i++)
    {
        if (memory.find(i) != memory.end()) continue;

        int nControl = i / shiftControl;
        bool controlIsOne = nControl % 2 == 1;

        int nTarget = i / shiftTarget;
        bool targetIsOne = nTarget % 2 == 1;

        int a = -1, b = -1, c = -1, d = -1;

        if(controlIsOne)
        {
            if (targetIsOne) {
                d = i;
                c = i - shiftTarget;
                b = d - shiftControl;
                a = b - shiftTarget;
            } else {
                c = i;
                d = c + shiftTarget;
                b = d - shiftControl;
                a = b - shiftTarget;
            }
        } else {
            if (targetIsOne) {
                b = i;
                a = b - shiftTarget;
                c = a + shiftControl;
                d = c + shiftTarget;
            } else {
                a = i;
                b = a + shiftTarget;
                c = a + shiftControl;
                d = c + shiftTarget;
            }
        }

        memory[a] = true;
        memory[b] = true;
        memory[c] = true;
        memory[d] = true;

        pairs.push_back({
            {a, this->amplitudes[a]},
            {b, this->amplitudes[b]},
            {c, this->amplitudes[c]},
            {d, this->amplitudes[d]}
        });
    }
    return pairs;
}

