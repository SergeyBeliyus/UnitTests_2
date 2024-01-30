cmake_minimum_required(VERSION 3.10)
project(UnitTests1)

add_subdirectory(./Catch2 Catch2-build)
add_executable(UnitTests1 test.cpp)
target_link_libraries(UnitTests1 PRIVATE Catch2::Catch2)
