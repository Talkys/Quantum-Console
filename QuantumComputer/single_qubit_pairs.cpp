#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <memory>
#include <string>
#include <iomanip>

template <typename T>
using Matrix = std::vector<std::vector<T>>;

class PairCache {
public:
    Matrix<std::complex<double>>* load(int key) {
        std::string filename = std::to_string(key) + ".txt";
        std::ifstream file(filename);
        if(!file.is_open()) return nullptr;

        Matrix<std::complex<double>>* matrix = new Matrix<std::complex<double>>();

        std::string line;
        while(std::getline(file, line)) {
            std::vector<std::complex<double>> row;
            size_t pos = 0;
            while(pos < line.size()) {
                double real, imag;
                sscanf(line.c_str() + pos, "%lf / %lf", &real, &imag);
                row.push_back(std::complex<double>(real, imag));
                pos = line.find(",", pos);
                if(pos == std::string::npos) break;
                pos++; // Pular vírgula
            }
            matrix->push_back(row);
        }
        file.close();
        return matrix;
    }

    bool save(int key, const Matrix<std::complex<double>> &data) {
        std::string filename = std::to_string(key) + ".txt";
        std::ofstream file(filename);

        if(!file.is_open()) {
            return false;
        }

        for(const auto& row : data) {
            for(size_t i = 0; i < row.size(); i++) {
                file << std::fixed << std::setprecision(10) << row[i].real() << " / " << row[i].imag();
                if(i < row.size() -1) {
                    file << ", ";
                }
            }
            file<<std::endl;
        }
        file.close();
        return true;
    }
};
