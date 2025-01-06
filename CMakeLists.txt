# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project name
project(memory_manager)

# Include directories (header files)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add the executable target
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/timer.cpp
    src/data.c
    src/memory.c
    src/memory_manager.c
    src/command.cpp
)