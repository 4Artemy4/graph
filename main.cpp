//#include <iostream>
//#include "Graph.h"
//
//int main() {
//    Graph<std::string> graph(0);
//    graph.addVertex("one");
//    graph.addVertex("two");
//    graph.addVertex("three");
//    graph.addVertex("four");
//
////    std::cout << graph.getEdgesCount() << '\n';
//    graph.addEdge(0, 1, 4);
//    graph.addEdge(2, 1, 7);
//    graph.addEdge(2, 0, 3);
////    std::cout << graph.getEdgesCount() << '\n';
////    graph.beginE();
//
//    for (auto i = graph.beginV(); i != graph.endV(); ++i) {
//        std::cout << *i << '\n';
//    }
//    std::cout << *graph.endV() << '\n';
//
//    std::cout << '\n';
//
//    for (auto i = graph.endV(); i != graph.beginV(); --i) {
//        std::cout << *i << '\n';
//    }
//    std::cout << *graph.beginV() << '\n';
//
//    std::cout << '\n';
//
//    for (auto i = graph.beginE(); i != graph.endE(); ++i) {
//        std::cout << *(*(*i).first) << "   " << *(*(*i).second) << "   " << (*i).weight << '\n';
//    }
//    std::cout << *(*(*graph.endE()).first) << "   " << *(*(*graph.endE()).second) << "   " << (*graph.endE()).weight
//              << '\n';
//
//    std::cout << '\n';
//
//    for (auto i = graph.endE(); i != graph.beginE(); --i) {
//        std::cout << *(*(*i).first) << "   " << *(*(*i).second) << "   " << (*i).weight << '\n';
//    }
//    std::cout << *(*(*graph.beginE()).first) << "   " << *(*(*graph.beginE()).second) << "   "
//              << (*graph.beginE()).weight << '\n';
//
////    graph.addVertex(0);
////    graph.addVertex(1);
////    graph.addVertex(2);
////    graph.addVertex(3);
////
////    for (auto i = graph.beginV(); i != graph.endV(); ++i) {
////        std::cout << *i << '\n';
////    }
//
//    for (const auto &i: graph) {
//        std::cout << i << '\n';
//    }
//    return 0;
//}
