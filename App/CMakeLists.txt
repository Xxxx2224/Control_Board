
cmake_minimum_required(VERSION 3.23)

if(CMAKE_CROSSCOMPILING)
    add_library(AppLib INTERFACE)
    
add_subdirectory(Error)
add_subdirectory(Control)
add_subdirectory(Drivers) 

target_sources(AppLib INTERFACE )
    target_link_libraries(AppLib INTERFACE Error Control Drivers) 

else()
Project(testprj)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Error)
add_subdirectory(Control)
add_subdirectory(Drivers) 

add_subdirectory(Test/Cpputest)
add_subdirectory(Test)

endif()
