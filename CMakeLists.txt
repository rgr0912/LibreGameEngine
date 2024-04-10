cmake_minimum_required(VERSION 3.10)

project(Testing VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/ogre)

add_executable(testing src/testing.cpp)

target_link_libraries(testing OgreMain OgreBites)

target_include_directories(testing PUBLIC ${CMAKE_SOURCE_DIR}/include)
