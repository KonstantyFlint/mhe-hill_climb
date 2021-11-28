cmake_minimum_required(VERSION 3.17)
project(mhe_plecak)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -lstdc++ -lpthread")

add_executable(mhe_plecak
        main.cpp)