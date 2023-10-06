#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
#include <iostream>

class Circuit
{
private:
    std::vector<std::string> circuit;
    void insertColumn(std::string);
public:
    Circuit(int);
    void insertGate(char, int, int);
    std::vector<std::string> getScreen();
};

Circuit::Circuit(int qubits)
{
    if(qubits < 1) return;
    std::string spacer = "";
    for(int i = 0; i < qubits; i++)
    {
        this->circuit.push_back("|" + std::to_string(i) + ">");
        spacer += "-";
    }
    insertColumn(spacer);
}

void Circuit::insertGate(char gate, int control, int target = -1)
{
    std::string column;
    for(int i = 0; i < this->circuit.size(); i++)
        column += "-";

    column[control] = gate;
    if(target != -1) column[target] = 'o';
    this->insertColumn(column);
    column[control] = '-';
    if(target != -1) column[target] = '-';
    this->insertColumn(column);
}

std::vector<std::string> Circuit::getScreen()
{
    return this->circuit;
}

void Circuit::insertColumn(std::string column)
{
    if(column.length() != this->circuit.size()) return;

    for(int i = 0; i < column.length(); i++)
    {
        this->circuit[i] += column[i];
    }
}

#endif // UI_H
