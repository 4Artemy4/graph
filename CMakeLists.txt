cmake_minimum_required(VERSION 3.17)
project(laba4)

add_subdirectory(test/googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(laba4 main.cpp graph/Graph.h test.cpp test.h GUI/MainWindow.cpp GUI/MainWindow.h test/allTests.cpp graph/VertexIterator.h graph/EdgesIterator.h)
target_link_libraries(laba4 gtest gtest_main)