cmake_minimum_required(VERSION 3.15)

project(cpp_backtester VERSION 0.1.0 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the main executable
add_executable(cpp_backtester
    src/main.cpp
)
