cmake_minimum_required(VERSION 3.5)
project(BinaryTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BinaryTree.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
