#include "quantumcomputer.h"

void QuantumComputer::applySingleBitMatrix(
    int offset,
    const Matrix<std::complex<double>>& matrix
) {
    Matrix<std::pair<int, std::complex<double>>> pairs = this->getSingleQubitPairs(offset);
    for (int i = 0; i < pairs.size(); i++) {
        std::vector<std::pair<int, std::complex<double>>> pair = pairs[i];
        std::complex<double> a = pair[0].second;
        std::complex<double> b = pair[1].second;
        Matrix<std::complex<double>> r = this->multiply(matrix, {{a}, {b}});
        this->amplitudes[pair[0].first] = r[0][0];
        this->amplitudes[pair[1].first] = r[1][0];
    }
}

void QuantumComputer::applyTwoBitsMatrix(
    int control,
    int target,
    const Matrix<std::complex<double>>& matrix
) {
    Matrix<std::pair<int, std::complex<double>>> pairs = this->getTwoQubitsPairs(control, target);
    int entagled = -1;

    for(int i = 0; i < pairs.size(); i++)
    {
        auto pair = pairs[i];
        std::complex<double> a = pair[0].second,
                             b = pair[1].second,
                             c = pair[2].second,
                             d = pair[3].second;

        Matrix<std::complex<double>> r = multiply(matrix, {{a}, {b}, {c}, {d}});

        this->amplitudes[pair[0].first] = r[0][0];
        this->amplitudes[pair[1].first] = r[1][0];
        this->amplitudes[pair[2].first] = r[2][0];
        this->amplitudes[pair[3].first] = r[3][0];

        if(entagled != -1) continue;

        auto a2 = r[0][0] * r[0][0],
             b2 = r[1][0] * r[1][0],
             c2 = r[2][0] * r[2][0],
             d2 = r[3][0] * r[3][0];

        auto pc_0 = a2 + b2,
             pc_1 = c2 + d2,
             pt_0 = a2 + c2,
             pt_1 = b2 + d2;

        if(!(std::abs(pc_0 * pt_0 - a2) < 1e-10 &&
             std::abs(pc_0 * pt_1 - b2) < 1e-10 &&
             std::abs(pc_1 * pt_0 - c2) < 1e-10 &&
             std::abs(pc_1 * pt_1 - d2) < 1e-10))
        {
            entagled = 1;
            this->twoBitsEntanglements[control] = target;
            this->twoBitsEntanglements[target] = control;
        } else {
            entagled = 0;
            this->twoBitsEntanglements.erase(control);
            this->twoBitsEntanglements.erase(target);
        }
    }
}
