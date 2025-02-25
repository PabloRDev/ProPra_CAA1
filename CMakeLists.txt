#cmake_minimum_required(VERSION 3.29)
#project(20242_P1 C)
#
#set(CMAKE_C_STANDARD 11)
#
#add_executable(20242_P1 main.c)

cmake_minimum_required(VERSION 3.29)
project(20242_P1 C)

set(CMAKE_C_STANDARD 11)

# Add header files (not required in add_executable but good for organization)
include_directories(${CMAKE_SOURCE_DIR})

# List all source files
add_executable(20242_P1 main.c subscription.c csv.c csv.h subscription.h)


