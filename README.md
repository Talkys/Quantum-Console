# Quantum Console
 Quantum Console is an educational quantum circuit simulator made to help studends and enthusiasts learn how quantum computing works beyond complex APIs like Qiskit.

## Instalation
I've made this in Qt Creator, so importing the project will be enough. For manual builds, refer to the CMake way:

```sh
mkdir build # outside project folder
cd build
cmake /path/to/project
make
```

## How to use

Quantum Console is used with verbose instructions

### start with n

Initializes the quantum computer with n qubits

### add \<gate> n

Add a gate to the n qubit in the register. You can use -t to set the target for 2 qubit gates like: add \<gate> n -t m

#### gates

The gates implemented are:

> I X Y Z T S H + (cnot) s (sdg) t (tdg)

### measure

Measure will collapse all qubits and halt the computer

### fake

This is a fake measure. It will select a possible value for the register but will not collapse the qubits. It's for test and debug purposes.

### poweroff

Will shut the computer down (the virtual one). Use this to reset the setup without reopening the program.

### quit

Closes the program