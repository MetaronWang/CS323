cmake_minimum_required(VERSION 3.14)
project(project2 LANGUAGES CXX)
set_source_files_properties(pro_3.tab.c PROPERTIES LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 14)
include_directories(.)

set(PROJECT_HEADERS
#        node.hpp
#        pro_3.tab.h
        )
set(PROJECT_SOURCES
        pro_3.tab.c
#        lex.yy.c
#        type.cpp
        )
add_executable(project3 ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(testCode testCode.cpp)