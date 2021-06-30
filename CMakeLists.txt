cmake_minimum_required(VERSION 3.10.2)
project(riscv_simulation_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(riscv_simulation_1 main.cpp program.h my_tools.h)
