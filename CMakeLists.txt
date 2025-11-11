cmake_minimum_required(VERSION 4.0)
project(Lab_9 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Lab_9
        gates.c
        gates.h
        logic_simulator.c
        logic_simulator_circuit.c
        logic_simulator_circuit_n.c)
