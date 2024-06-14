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

Quantum console is a code API. You can use it like Quiskit

### Initialization

QuantumComputer(int seed) will create a new object with a seed for random generation
boot(int N) will start the computer with N qubits

### Gates

To add gates to the computer use the following functions

(id, x, y, z, t, tdg, s, sdg, h) with a single int parameter that is the target qubit index 0-based

cnot with two parameters: the control and target qubits

### Measuring

To colapse the computer and get a result you can use measuerQreg()

To do a fake measurement you can use fakemeasure(int seed) with a seed for random generation
