
cmake_minimum_required(VERSION 3.22)
project(ipc_benchmark CXX)

message("-----------------------------------------------------------------------")
message("IPC Benchmarking for Embedded Applications")
message("Developed by Parham Nooralishahi (PHM66)")
message("Website: https://parhamnooralishahi.me/")
message("GitHub: https://github.com/parham")
message("-----------------------------------------------------------------------")

set(CMAKE_C_FLAGS "-pthread -std=gnu99")
set(CMAKE_CXX_FLAGS "-std=c++11 -pthread -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "-pthread")
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-D_GNU_SOURCE)


