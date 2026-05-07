add_executable(cpptest)
target_sources(cpptest 
            PRIVATE
            Src/testcpp.cpp)

target_link_libraries(cpptest PRIVATE CppUTest Control)
