cmake_minimum_required(VERSION 4.0)
project(Pong_in_c C)

set(CMAKE_C_STANDARD 11)

# Find SDL3 package
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

# Add your executable
add_executable(Pong_in_c pong.c)

# Link SDL3 to your executable
target_link_libraries(Pong_in_c PRIVATE SDL3::SDL3)