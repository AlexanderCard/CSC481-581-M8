cmake_minimum_required(VERSION 3.16)
project(PropertyCentricModelSDL3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

add_executable(component_model
    src/main.cpp src/GameObject.cpp src/GameObject.hpp
)

target_link_libraries(component_model PRIVATE SDL3::SDL3)
