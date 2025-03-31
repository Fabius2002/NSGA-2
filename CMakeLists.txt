cmake_minimum_required(VERSION 3.30)
project(NSGA_2)

set(CMAKE_CXX_STANDARD 20)

option(DEBUG "Enable debug functionality" OFF)

if(DEBUG)
    add_definitions(-DDEBUG)
endif()

option(EXPORT "Enable export functionality" OFF)

if(EXPORT)
    add_definitions(-DEXPORT)
endif()


add_compile_definitions(POPULATION_SIZE=100)
add_compile_definitions(GENERATION_COUNT=100)
add_compile_definitions(CROSSOVER_ALPHA=0.5)
add_compile_definitions(MUTATION_DISTRIBUTION=20)
add_compile_definitions(MUTATION_PROBABILITY=0.5)
add_compile_definitions(NOISE=5)

add_executable(NSGA_2 main.cpp
        Problem.hpp
        NSGA.hpp
        Help.hpp
        NSGA.cpp
        Help.cpp
        Crossover.hpp
        Crossover.cpp
        Mutator.hpp
        Mutator.cpp
        Export.hpp
        Export.cpp
        Debug.cpp
        Debug.hpp
)
