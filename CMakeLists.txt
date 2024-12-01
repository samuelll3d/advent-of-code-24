cmake_minimum_required(VERSION 3.30)
project(advent-of-code-24 C)

set(CMAKE_C_STANDARD 11)

include_directories(src/day_1/)

add_executable(day_1_part_1 src/day_1/day_1_part_1.c)
add_executable(day_1_part_2 src/day_1/day_1_part_2.c)
