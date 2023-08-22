
cmake_minimum_required(VERSION 3.22)
project(ipc_benchmark CXX)

message("-----------------------------------------------------------------------")
message("IPC Benchmarking for Embedded Applications")
message("Developed by Parham Nooralishahi (PHM66)")
message("Website: https://parhamnooralishahi.me/")
message("GitHub: https://github.com/parham")
message("-----------------------------------------------------------------------")

set(CMAKE_C_FLAGS "-pthread -std=gnu99")
set(CMAKE_CXX_FLAGS "-std=c++17 -pthread -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "-pthread")
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-D_GNU_SOURCE)

# Initialize the result directory
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/results)

# Set the header files
include_directories(${PROJECT_SOURCE_DIR}/src)

# Set the source code for modules and components
file(GLOB_RECURSE PHM_IPC_MODULE_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE PHM_IPC_MODULE_HR ${PROJECT_SOURCE_DIR}/src/*.h)

message(STATUS "Source files: ${PHM_IPC_MODULE_SRC}")
message(STATUS "Header files: ${PHM_IPC_MODULE_HR}")

add_library(
    ${PROJECT_NAME} STATIC
    ${PHM_IPC_MODULE_HR}
    ${PHM_IPC_MODULE_SRC}
)

# Set the source code for the main program
set(IPC_APP_SRC main.cpp)

add_executable(phm_ipc ${IPC_APP_SRC})
target_link_libraries(phm_ipc PRIVATE ${PROJECT_NAME})

# Find Boost
find_package(Boost REQUIRED)
message(STATUS "Found Boost installed in the system")
message(STATUS " - Includes: ${Boost_INCLUDE_DIRS}")
message(STATUS " - Libraries: ${Boost_LIBRARY_DIRS}")
message(STATUS " - Definitions: ${Boost_DEFINITIONS}")

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
add_definitions(${Boost_DEFINITIONS})

# Determine where to place the execution files
if (NOT EXECUTABLE_OUTPUT_PATH)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
endif ()

# ---------------------------------
# UNIT TESTING
# ---------------------------------

# Test for Boost shared memory
add_executable(test_boost_shm tests/test_boost_shm.cpp)
add_executable(test_boost_shm_2 tests/test_boost_shm_2.cpp)

# enable testing functionality
enable_testing()
add_test(
    NAME test_boost_shm
    COMMAND $<TARGET_FILE:test_boost_shm>
)
add_test(
        NAME test_boost_shm_2
        COMMAND $<TARGET_FILE:test_boost_shm_2>
)