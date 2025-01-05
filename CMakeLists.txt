# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project name
project(memory_manager)

# Include directories (header files)
include_directories(${CMAKE_SOURCE_DIR})

# Add the executable target
add_executable(${PROJECT_NAME}
    main.c
    data.c
    memory.c
    memory_manager.c
)