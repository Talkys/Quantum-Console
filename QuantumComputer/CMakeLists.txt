cmake_minimum_required(VERSION 3.5)

project(quantum_sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -O2")

add_executable(quantum_sim main.cpp
    quantum_computer.h
    quantum_computer.cpp
    quantum_computer_apply.cpp
    quantum_computer_gates.cpp
    quantum_computer_pairs.cpp
    quantum_computer_probability.cpp
    quantum_computer_utils.cpp
    single_qubit_pairs.cpp)

target_link_libraries(quantum_sim PRIVATE OpenMP::OpenMP_CXX)

include(GNUInstallDirs)
install(TARGETS quantum_sim
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
