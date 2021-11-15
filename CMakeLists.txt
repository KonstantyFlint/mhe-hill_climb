cmake_minimum_required(VERSION 3.17)
project(mhe_plecak)

set(CMAKE_CXX_STANDARD 14)

add_executable(mhe_plecak
        main.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/problem.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})