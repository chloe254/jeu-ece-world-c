cmake_minimum_required(VERSION 3.23)
project(tchernobyl C)

set(CMAKE_C_STANDARD 99)

add_executable(tchernobyl main.c)
target_link_libraries(tchernobyl -lmingw32 -lalleg44)
