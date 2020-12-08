//
// Created by art on 11/24/20.
//

#include "gtest/gtest.h"
#include "../gr/Graph.h"

class TestGraph : public testing::Test {
protected:
    TestGraph() {
        graph = graph::Graph<size_t, size_t>(3);
    }

    graph::Graph<size_t, size_t> graph;
};

TEST_F(TestGraph, TestVertexItearator) {
    auto j = graph.beginV();
    *j = 1;
    ++j;
    *j = 2;
    *(++j) = 3;
    graph.addVertex(4);

    std::vector<size_t> test;
    for (auto i = graph.beginV(); i != graph.endV(); ++i) {
        test.push_back(*i);
    }
    std::vector<size_t> real;
    real.push_back(1);
    real.push_back(2);
    real.push_back(3);
    real.push_back(4);
    ASSERT_EQ(test, real);
}

TEST_F(TestGraph, ConstVertexIterator) {
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    std::vector<size_t> test;
    for (auto i = graph.cbeginV(); i != graph.cendV(); ++i) {
        test.push_back(*i);
    }
    std::vector<size_t> real(3);
    real.push_back(1);
    real.push_back(2);
    real.push_back(3);
    ASSERT_EQ(test, real);
}

TEST_F(TestGraph, ReverseVertexIterator) {
    *graph.rbeginV() = -1;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    std::vector<size_t> test;
    for (auto i = graph.rbeginV(); i != graph.rendV(); --i) {
        test.push_back(*i);
    }
    std::vector<size_t> real(3);
    real.at(0) = -1;
    real.push_back(1);
    real.push_back(2);
    real.push_back(3);
    ASSERT_EQ(test, real);
}

TEST_F(TestGraph, EdgesIterator) {
    *graph.beginV() = 1;
    *++graph.beginV() = 2;
    *++(++graph.beginV()) = 3;
    *(*graph.beginE()).weight = 222;
    graph.addVertex(4);
    graph.addVertex(5);
    graph.addEdge(0, 1, 4);
    graph.addEdge(1, 2, 12);
}

TEST_F(TestGraph, ConstEdgesIterator) {
    auto x = graph.cbeginE();
    auto y = graph.cendE();
}

TEST_F(TestGraph, ReverseEdgesIterator) {
    *graph.rbeginV() = 1;
    *--graph.rbeginV() = 2;
    *--(++graph.rbeginV()) = 3;
    *(*graph.rbeginE()).weight = 222;
    graph.addVertex(4);
    graph.addVertex(5);
    graph.addEdge(0, 1, 4);
    graph.addEdge(1, 2, 12);
}

TEST_F(TestGraph, add_removeVertex) {
    ASSERT_TRUE(graph.getVertexesCount() == 3);
    graph.addVertex(5);
    ASSERT_TRUE(graph.getVertexesCount() == 4);
    graph.removeVertex(1);
    ASSERT_TRUE(graph.getVertexesCount() == 3);
    graph.addVertex(12);
    ASSERT_TRUE(graph.getVertexesCount() == 4);
    graph.removeVertex(++graph.beginV());
    ASSERT_TRUE(graph.getVertexesCount() == 3);
}

TEST_F(TestGraph, add_removeEdges) {
    ASSERT_TRUE(graph.getEdgesCount() == 0);
    graph.addEdge(0, 0, 5);
    ASSERT_TRUE(graph.getEdgesCount() == 1);
    graph.addEdge(2, 1, 2);
    ASSERT_TRUE(graph.getEdgesCount() == 2);
    graph.addEdge(++graph.beginE(), 8);
    ASSERT_TRUE(graph.getEdgesCount() == 3);
    graph.removeEdges(1, 2);
    ASSERT_TRUE(graph.getEdgesCount() == 2);

}

TEST_F(TestGraph, equality) {
    graph::Graph<size_t, size_t> graph2(3);
    ASSERT_TRUE(graph == graph2);
    graph2.addEdge(0, 1, 4);
    graph.addEdge(0, 1, 3);
    ASSERT_TRUE(graph != graph2);
    graph.addEdge(0, 1, 4);
    ASSERT_TRUE(graph == graph2);
    graph2.addVertex(4);
    ASSERT_TRUE(graph != graph2);
    graph.addVertex(3);
    ASSERT_TRUE(graph != graph2);
    *--graph.endV() = 4;
    ASSERT_TRUE(graph == graph2);
}

TEST_F(TestGraph, empty_clear) {
    ASSERT_FALSE(graph.empty());
    graph.clear();
    ASSERT_TRUE(graph.empty());
    graph.addVertex(2);
    ASSERT_FALSE(graph.empty());
    graph.addEdge(0, 0, 3);
}

TEST_F(TestGraph, OtherFunctionsTest) {
    *graph.beginV() = 1;
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(0, 2, 9);
    graph.addEdge(1, 2, 12);

    ASSERT_TRUE(graph.isVertexExist(0));
    ASSERT_TRUE(graph.isVertexExist(4));
    ASSERT_FALSE(graph.isVertexExist(6));
    ASSERT_FALSE(graph.isVertexExist(-1));
    ASSERT_TRUE(graph.getVertexesCount() == 5);
    ASSERT_TRUE(graph.getEdgesCount() == 2);
    ASSERT_TRUE(graph.isEdgeExist(0, 2));
    ASSERT_TRUE(graph.isEdgeExist(2, 1));
    ASSERT_FALSE(graph.isEdgeExist(2, 3));
    ASSERT_TRUE(graph.neighborsCount(2) == 2);

    graph.removeVertex(2);

    ASSERT_TRUE(graph.isVertexExist(graph.beginV()));
    ASSERT_TRUE(graph.isVertexExist(3));
    ASSERT_FALSE(graph.isVertexExist(4));
    ASSERT_FALSE(graph.isVertexExist(-1));
    ASSERT_TRUE(graph.getVertexesCount() == 4);
    ASSERT_TRUE(graph.getEdgesCount() == 0);
    ASSERT_FALSE(graph.isEdgeExist(0, 2));
    ASSERT_FALSE(graph.isEdgeExist(2, 1));
    ASSERT_FALSE(graph.isEdgeExist(2, 3));
    ASSERT_TRUE(graph.neighborsCount(2) == 0);
}
