cmake_minimum_required(VERSION 3.17)
project(laba4)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_executable(laba4 main.cpp GUI/MainWindow.h test/allTests.cpp gr/Graph.h gr/VertexIterator.h gr/EdgesIterator.h gr/ConstVertexIterator.h gr/ReverseVertexIterator.h gr/ConstEdgesIterator.h gr/ReverseEdgesIterator.h GUI/GraphWindow.h GUI/Node.h)
target_link_libraries(laba4 gtest gtest_main)
target_link_libraries(laba4 ${Qt5Widgets_LIBRARIES})