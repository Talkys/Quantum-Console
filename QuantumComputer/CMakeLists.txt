cmake_minimum_required(VERSION 3.5)

project(QuantumComputer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    QuantumComputer
    quantumcomputer_utils.cpp
    quantumcomputer.cpp
    quantumcomputer_pairs.cpp
    quantumcomputer_probability.cpp
    quantumcomputer_gates.cpp
    quantumcomputer_apply.cpp
    quantumcomputer.h
    parser.h
    UI.h
    main.cpp
)

install(TARGETS QuantumComputer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
