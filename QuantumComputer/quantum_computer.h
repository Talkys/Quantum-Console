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
    //Número de qubits no circuito
    unsigned int                      qubitRegNum;

    //Mapa que rastreia o entrelaçamento de qubits
    std::map<int, int>                twoBitsEntanglements;

    //Vetor de amplitudes, representado como um vetor de números complexos

    //Cada qubit é representado por uma combinação linear de dois
    //números complexos
    std::vector<std::complex<double>> amplitudes;

    //Seed para o rng global. Estando aqui ela pode ser setada ao construir o objeto
    int                               rngSeed;

    //Função genérica para multiplicar matrizes de números complexos
    Matrix<std::complex<double>> multiply(
        const Matrix<std::complex<double>>& A,
        const Matrix<std::complex<double>>& B
        );

    /*
     Agrupa qubits usando um qubit de alvo
     */
    Matrix<std::pair<int, std::complex<double>>>
    getSingleQubitPairs(unsigned int);

    /*
     Agrupa qubits usando dois qubits de alvo
     */
    Matrix<std::pair<int, std::complex<double>>>
    getTwoQubitsPairs(int, int);

    /*Calcula a probabilidade de estados de um único qubit*/
    std::vector<double> getQubitProbability(int offset);

    /*Calcula a probabilidade de um conjunto de qubits*/
    double getQubitsProbability(
        const std::vector<int>& offsets,
        const std::vector<int>& targets
        );

    /*Aplica uma matriz unitária em um qubit*/
    void applySingleBitMatrix(
        int offset,
        const Matrix<std::complex<double>>& matrix
        );

    /*Aplica uma matriz dupla em dois qubits
     Aqui é usada somente para a porta cnot*/
    void applyTwoBitsMatrix(
        int control,
        int target,
        const Matrix<std::complex<double>>& matrix
        );

public:
    /*Construtor. Setar a seed para inicializar*/
    QuantumComputer(int);

    /*
     Inicializa o computador com N qubits
     Recebe: Número de qubits, número de bits para o registrador regular
     */
    void boot(unsigned int);

    /*
     Aqui tem uma coleção de portas que estão implementadas no simulador
     Cada uma tem sua especificação detalhada em um documento separado
     */


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

    /*Mede o registrador colapsando qubits*/
    int measureQreg();

    /*Mede o registrador sem colapsar qubits*/
    int fakemeasure(int);
};

#endif // QUANTUMCOMPUTER_H
