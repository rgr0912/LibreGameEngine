cmake_minimum_required(VERSION 3.0.0)

project(Testing VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(testing src/testing.cpp)

target_include_directories(testing PUBLIC ${CMAKE_SOURCE_DIR}/include)
