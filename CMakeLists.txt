cmake_minimum_required(VERSION 4.1)
project(IAHomework)

set(CMAKE_CXX_STANDARD 20)

add_executable(IAHomework main.cpp
        src/dsf_and_bfs_1.cpp
        include/dsf_and_bfs_1.h
        src/binaryTree.cpp
        include/binaryTree.h)
