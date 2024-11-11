cmake_minimum_required(VERSION 3.14)
project(first)

set(CMAKE_CXX_STANDARD 26)

set(SOURCE_FILES main.cpp
        Particle.cpp
        Particle.h
        Particle_container.cpp
        Particle_container.h
        Utils.cpp
        Utils.hpp
        Control_rod.cpp
        Quad_tree.hpp
        Control_rod.hpp
)
add_executable(first ${SOURCE_FILES})

set(SFML_DIR "/usr/local/include/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(first sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
