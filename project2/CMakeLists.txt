cmake_minimum_required(VERSION 3.14)
project(project2 LANGUAGES CXX)
set_source_files_properties(pro_2.tab.c PROPERTIES LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 14)
include_directories(.)

set(PROJECT_HEADERS
#        node.hpp
#        pro_2.tab.h
        )
set(PROJECT_SOURCES
        pro_2.tab.c
#        lex.yy.c
#        type.cpp
        )
add_executable(project2 ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(testCode testCode.cpp)