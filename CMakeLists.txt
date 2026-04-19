cmake_minimum_required(VERSION 3.20)
project(IAHomework)

set(CMAKE_CXX_STANDARD 20)

add_executable(IAHomework
        main.cpp
        src/dsf_and_bfs_1.cpp
        include/dsf_and_bfs_1.h
        src/binaryTree.cpp
        include/binaryTree.h
        include/graph.h
        src/math_test.cpp
        include/math/math_test.h
        include/math/math.h
        include/math/core.h
        include/math/calculus.h
        include/math/linear_algebra.h
        include/math/types.h
        include/math/constants.h
        include/math/linear_algebra/Vec.h
        include/math/linear_algebra/Matrix.h
        include/math/linear_algebra/Tensor.h
)



