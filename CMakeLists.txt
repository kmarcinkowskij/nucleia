cmake_minimum_required(VERSION 3.14)
project(first)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp
        Particle.cpp
        Particle.h
        Particle_container.cpp
        Particle_container.h
        Utils.cpp
        Utils.hpp
)
add_executable(first ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(first sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
