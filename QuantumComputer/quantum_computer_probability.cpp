
#include "quantum_computer.h"

double QuantumComputer::getQubitsProbability
    (
        const std::vector<int>& offsets,
        const std::vector<int>& targets
        ) {
    double probability = 0.0;

    int amplitudes_size = this->amplitudes.size();
    for(int i = 0; i < amplitudes_size; i++)
    {
        std::complex<double> amplitude = this->amplitudes[i];
        if(std::abs(amplitude) == 0)
            continue;

        bool found = true;
        for(int j = 0; j < offsets.size(); j++)
        {
            int offset = offsets[j];
            int target = targets[j];
            int shift = 1 << offset;
            int n = i / shift;

            if(n % 2 != target)
            {
                found = false;
                break;
            }
        }

        if(found)
            probability += std::abs(amplitude * amplitude);
    }
    return probability;
}
