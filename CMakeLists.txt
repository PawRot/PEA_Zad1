cmake_minimum_required(VERSION 3.26)
project(PEA_Zad1)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif(WIN32)

set(CMAKE_CXX_STANDARD 20)

add_executable(PEA_Zad1 menu/main.cpp
        data/dataGenerator.h
        data/dataGenerator.cpp
        data/fileOperator.h
        data/fileOperator.cpp
        algorithms/bruteForce.cpp
        algorithms/bruteForce.h
        algorithms/BranchBound.cpp
        algorithms/BranchBound.h
)
