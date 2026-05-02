cmake_minimum_required(VERSION 4.3.2)
Project(testprj)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Test/Cpputest)
add_subdirectory(Error)
add_subdirectory(Control)

add_executable(test)

target_sources(test PRIVATE Core/Src/main.c)

target_link_libraries(test PRIVATE CppUTest Error Control) 
