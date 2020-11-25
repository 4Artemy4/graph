//
// Created by art on 11/24/20.
//

#include "gtest/gtest.h"
#include "../graph/Graph.h"

TEST(VertexIterator, test){
    Graph<std::string> graph(3);
    std::vector<std::string> test;
    auto j = graph.beginV();
    *j = "1";
    ++j;
    *j = "2";
    *graph.endV() = "3";
    graph.addVertex("4");
    for (auto i = graph.beginV(); i != graph.endV(); ++i) {
        test.push_back(*i);
    }
    test.push_back(*graph.endV());
    std::vector<std::string> real;
    real.push_back("1");
    real.push_back("2");
    real.push_back("3");
    real.push_back("4");
    ASSERT_EQ(test, real);
}

TEST(ConstVertexIterator, test){
    Graph<int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    std::vector<int> test;
    for (auto i = graph.cbeginV(); i != graph.cendV(); ++i) {
        std::cout << *i;
//        test.push_back(*i);
    }
    test.push_back(*graph.cendV());
//    test.cbegin();
    std::vector<int> real;
    real.push_back(1);
    real.push_back(2);
    real.push_back(3);
    ASSERT_EQ(test, real);
}

TEST(ReverseVertexIterator, test){
    ASSERT_EQ(5, 5);
}

TEST(EdgesIterator, test){
    ASSERT_EQ(5, 5);
}

TEST(ConstEdgesIterator, test){
    ASSERT_EQ(5, 5);
}

TEST(ReverseEdgesIterator, test){
    ASSERT_EQ(5, 5);
}

TEST(OtherMethods, test){
    ASSERT_EQ(5, 5);
}
