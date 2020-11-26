//
// Created by art on 11/24/20.
//

#include "gtest/gtest.h"
#include "../graph/Graph.h"

class TestGraph: public testing::Test{
protected:
    TestGraph(){
        graph = Graph<size_t, size_t>(3);
    }
    Graph<size_t, size_t> graph;
};

TEST_F(TestGraph, TestVertexItearator){
    std::vector<size_t> test;
    auto j = graph.beginV();
    *j = 1;
    ++j;
    *j = 2;
    *graph.endV() = 3;
    graph.addVertex(4);
    for (auto i = graph.beginV(); i != graph.endV(); ++i) {
        test.push_back(*i);
    }
    test.push_back(*graph.endV());
    std::vector<size_t> real;
    real.push_back(1);
    real.push_back(2);
    real.push_back(3);
    real.push_back(4);
    ASSERT_EQ(test, real);
}

TEST_F(TestGraph, ConstVertexIterator){
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    std::vector<size_t> test;
    for (auto i = graph.cbeginV(); i != graph.cendV(); ++i) {
        test.push_back(*i);
    }
    test.push_back(*graph.cendV());
    std::vector<size_t> real(3);
    real.push_back(1);
    real.push_back(2);
    real.push_back(3);
    ASSERT_EQ(test, real);
}

TEST_F(TestGraph, ReverseVertexIterator){
    *graph.rBeginV() = -1;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    std::vector<size_t> test;
    for (auto i = graph.rBeginV(); i != graph.rEndV(); --i) {
        test.push_back(*i);
    }
    test.push_back(*graph.cendV());
    std::vector<size_t> real(3);
    real.at(0) = -1;
    real.push_back(1);
    real.push_back(2);
    real.push_back(3);
    ASSERT_EQ(test, real);
}

TEST_F(TestGraph, EdgesIterator){
    *graph.beginV() = 1;
    *(*graph.beginE()).weight = 222;
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(0, 2, 9);
    graph.addEdge(1, 2, 12);
    std::cout << graph;
}

TEST_F(TestGraph, OtherFunctionsTest){
    *graph.beginV() = 1;
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(0, 2, 9);
    graph.addEdge(1, 2, 12);
    ASSERT_TRUE(graph.isVertexExists(0));
    ASSERT_TRUE(graph.isVertexExists(4));
    ASSERT_FALSE(graph.isVertexExists(6));
    ASSERT_FALSE(graph.isVertexExists(-1));
    ASSERT_TRUE(graph.getVertexCount() == 5);
    ASSERT_TRUE(graph.getEdgesCount() == 2);
    ASSERT_TRUE(graph.isEdgeExists(0, 2));
    ASSERT_TRUE(graph.isEdgeExists(2, 1));
    ASSERT_FALSE(graph.isEdgeExists(2, 3));
    ASSERT_TRUE(graph.neighborsCount(2) == 2);

    graph.removeVertex(2);

    ASSERT_TRUE(graph.isVertexExists(0));
    ASSERT_TRUE(graph.isVertexExists(3));
    ASSERT_FALSE(graph.isVertexExists(4));
    ASSERT_FALSE(graph.isVertexExists(-1));
    ASSERT_TRUE(graph.getVertexCount() == 4);
    ASSERT_TRUE(graph.getEdgesCount() == 0);
    ASSERT_FALSE(graph.isEdgeExists(0, 2));
    ASSERT_FALSE(graph.isEdgeExists(2, 1));
    ASSERT_FALSE(graph.isEdgeExists(2, 3));
    ASSERT_TRUE(graph.neighborsCount(2) == 0);


}
