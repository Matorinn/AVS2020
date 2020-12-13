cmake_minimum_required(VERSION 3.17)
project(AVS5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-fopenmp")
add_executable(AVS5 main.cpp)
target_link_libraries(AVS5 pthread)