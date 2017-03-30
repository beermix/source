cmake_minimum_required(VERSION 2.6)

project(uinit)
set(CMAKE_C_FLAGS "-Wall")

add_executable(init main.c)
target_compile_definitions(init PUBLIC _GNU_SOURCE)
install(TARGETS init RUNTIME DESTINATION /)
