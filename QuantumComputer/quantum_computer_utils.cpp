#include "quantum_computer.h"

int QuantumComputer::measureQreg() {
    // Calcula a soma dos quadrados dos módulos das amplitudes
    double somaQuadrados = 0.0;
    for (const std::complex<double>& amplitude : amplitudes) {
        double moduloQuadrado = std::norm(amplitude);
        somaQuadrados += moduloQuadrado;
    }
    std::random_device rd;
    std::mt19937 rng(rd());
    rng.seed(this->rngSeed);
    // Gera um número aleatório entre 0 e a soma dos quadrados
    double numeroAleatorio = static_cast<double>(rng()) / RAND_MAX * somaQuadrados;
    while(numeroAleatorio > 1)
        numeroAleatorio = static_cast<double>(rng()) / RAND_MAX * somaQuadrados;
    //std::cerr<<numeroAleatorio<<std::endl;
    // Realiza a medição com base no número aleatório gerado
    double acumulado = 0.0;
    for (int i = 0; i < amplitudes.size(); ++i) {
        double moduloQuadrado = std::norm(amplitudes[i]);
        acumulado += moduloQuadrado;
        if (numeroAleatorio <= acumulado) {
            this->boot(this->qubitRegNum);
            this->amplitudes[0] = 0;
            this->amplitudes[i] = 1;
            return i; // Retorna o índice da amplitude medida
        }
    }

    // Se chegou até aqui, algo deu errado (isso não deveria acontecer)
    std::cerr << "Erro na medição!" << std::endl;
    return -1;
}

int QuantumComputer::fakemeasure(int seed) {
    // Calcula a soma dos quadrados dos módulos das amplitudes
    double somaQuadrados = 0.0;
    for (const std::complex<double>& amplitude : amplitudes) {
        double moduloQuadrado = std::norm(amplitude);
        somaQuadrados += moduloQuadrado;
    }
    std::random_device rd;
    std::mt19937 rng(rd());
    rng.seed(seed);
    // Gera um número aleatório entre 0 e a soma dos quadrados
    double numeroAleatorio = static_cast<double>(rng()) / RAND_MAX * somaQuadrados;
    while(numeroAleatorio > 1)
        numeroAleatorio = static_cast<double>(rng()) / RAND_MAX * somaQuadrados;
    //std::cerr<<numeroAleatorio<<std::endl;
    // Realiza a medição com base no número aleatório gerado
    double acumulado = 0.0;
    for (int i = 0; i < amplitudes.size(); ++i) {
        double moduloQuadrado = std::norm(amplitudes[i]);
        acumulado += moduloQuadrado;
        if (numeroAleatorio <= acumulado) {
            //Dessa vez não resetamos o computador, assim podemos testar, mas isso não acontece na vida real
            return i; // Retorna o índice da amplitude medida
        }
    }

    // Se chegou até aqui, algo deu errado (isso não deveria acontecer)
    std::cerr << "Erro na medição!" << std::endl;
    return -1;
}

Matrix<std::complex<double>> QuantumComputer::multiply(
    const Matrix<std::complex<double>>& A,
    const Matrix<std::complex<double>>& B
    ) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    if(colsA != rowsB)
        throw std::runtime_error(
            "Dimensoes das matrizes nao batem\n"
            );

    Matrix<std::complex<double>> result(rowsA, std::vector<std::complex<double>>(colsB, 0));

    for(int i = 0; i < rowsA; i++)
        for(int j = 0; j < colsB; j++)
            for(int k = 0; k < colsA; k++)
                result[i][j] += A[i][k] * B[k][j];

    return result;
}
