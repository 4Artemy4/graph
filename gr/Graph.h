//
// Created by art on 11/28/20.
//

#define vectorPtr(TYPE) std::shared_ptr<std::vector<TYPE>>
#define newVectorPtr(TYPE, size) std::shared_ptr<std::vector<TYPE>>(new std::vector<TYPE>(size))
#ifndef LABA4_GRAPH_H
#define LABA4_GRAPH_H

#include <memory>
#include <vector>
#include <ostream>
#include "VertexIterator.h"
#include "ConstVertexIterator.h"
#include "ReverseVertexIterator.h"
#include "EdgesIterator.h"
#include "ConstEdgesIterator.h"
#include "ReverseEdgesIterator.h"

namespace graph {

    template<typename NodeType, typename EdgeType>
    class Graph {
    protected:
        vectorPtr(NodeType) vertexes;
        vectorPtr(vectorPtr(EdgeType)) edges;

        typedef graph::VertexIterator<NodeType> vertexIter;
        typedef graph::ConstVertexIterator<NodeType> constVertexIter;
        typedef graph::ReverseVertexIterator<NodeType> reverseVertexIter;

        typedef graph::EdgesIterator<NodeType, EdgeType> edgesIter;
        typedef graph::ConstEdgesIterator<NodeType, EdgeType> constEdgesIter;
        typedef graph::ReverseEdgesIterator<NodeType, EdgeType> reverseEdgesIter;

        typedef Graph<NodeType, EdgeType> GraphType;

    public:
        Graph() {
            vertexes = newVectorPtr(NodeType, 0);
            edges = std::shared_ptr<std::vector<std::shared_ptr<std::vector<EdgeType>>>>(
                    new std::vector<std::shared_ptr<std::vector<EdgeType>>>(0));
            edges.get();
        }

        Graph(size_t size) {
            vertexes = newVectorPtr(NodeType, size);
            edges = std::shared_ptr<std::vector<std::shared_ptr<std::vector<EdgeType>>>>(
                    new std::vector<std::shared_ptr<std::vector<EdgeType>>>(size));
            for (int i = 0; i < size; ++i) {
                edges.get()->at(i) = newVectorPtr(EdgeType, size);
            }
        }

        Graph(const GraphType &rhs) {
            for (int i = 0; i < vertexes.get()->size(); ++i) {
                this->addVertex(rhs.vertexes.get()->at(i));
            }
            for (int i = 0; i < edges.get()->size(); ++i) {
                for (int j = 0; j < edges.get()->size(); ++j) {
                    this->addVertex(rhs.edges.get()->at(i).get()->at(j));
                }
            }
        }

        Graph &operator=(const GraphType &rhs) {
            vertexes = rhs.vertexes;
            edges = rhs.edges;
            return *this;
        }

        bool operator==(const GraphType &rhs) const {
            if (vertexes.get()->size() != rhs.vertexes.get()->size()) return false;
            for (int i = 0; i < vertexes.get()->size(); ++i) {
                if (vertexes.get()->at(i) != rhs.vertexes.get()->at(i)) return false;
            }
            for (int i = 0; i < edges.get()->size(); ++i) {
                for (int j = 0; j < edges.get()->size(); ++j) {
                    if (edges.get()->at(i).get()->at(j) != rhs.edges.get()->at(i).get()->at(j)) return false;
                }
            }
            return true;
        }

        bool operator!=(const GraphType &rhs) const {
            return !(*this == rhs);
        }

        friend std::ostream &operator<<(std::ostream &os, const Graph &graph1) {
            for (auto i = graph1.cbeginE(); i != graph1.cendE(); ++i) {
                os << *(*i).iter1 << "--" << *(*i).iter2 << "  " << *(*i).weight << '\n';
            }
            return os;
        }

        std::string print() const {
            std::string result;
            for (auto i = cbeginE(); i != cendE(); ++i) {
                result += *(*i).iter1 + "--" << *(*i).iter2 + "  " + *(*i).weight + '\n';
            }
            return result;
        }

        bool empty() const {
            return vertexes.get()->size() == 0;
        }

        void clear() {
            vertexes = newVectorPtr(NodeType, 0);
            edges = std::shared_ptr<std::vector<std::shared_ptr<std::vector<EdgeType>>>>(
                    new std::vector<std::shared_ptr<std::vector<EdgeType>>>(0));
        }

        void addVertex(NodeType data) {
            edges.get()->push_back(newVectorPtr(EdgeType, vertexes.get()->size()));
            if (vertexes.get()->size() == 0) {
                edges.get()->at(0) = newVectorPtr(EdgeType, 0);
            }
            vertexes.get()->push_back(data);

            for (int i = 0; i < edges.get()->size(); ++i) {
                edges.get()->at(i).get()->push_back(0);
            }
        }

        void addEdge(edgesIter index, EdgeType data) const {
            edges.get()->at((*index).iter1.getIndex()).get()->at((*index).iter2.getIndex()) = data;
            edges.get()->at((*index).iter2.getIndex()).get()->at((*index).iter1.getIndex()) = data;
        }

        void addEdge(size_t index1, size_t index2, EdgeType data) const {
            edges.get()->at(index1).get()->at(index2) = data;
            edges.get()->at(index2).get()->at(index1) = data;
        }

        void addEdge(vertexIter index1, vertexIter index2, EdgeType data) const {
            edges.get()->at(index1.getIndex()).get()->at(index2.getIndex()) = data;
            edges.get()->at(index2.getIndex()).get()->at(index1.getIndex()) = data;
        }

        void removeVertex(size_t index) {
            vertexes.get()->erase(vertexes.get()->begin() + index);
            edges.get()->erase(edges.get()->begin() + index);
            for (int i = 0; i < edges.get()->size(); ++i) {
                edges.get()->at(i).get()->erase(edges.get()->at(i).get()->begin() + index);
            }
        }

        void removeVertex(vertexIter index) {
            removeVertex(index.getIndex());
        }

        void removeEdges(size_t index1, size_t index2) {
            edges.get()->at(index1).get()->at(index2) = 0;
            edges.get()->at(index2).get()->at(index1) = 0;
        }

        void removeEdges(edgesIter index) {
            edges.get()->at((*index).iter1.getIndex()).get()->at((*index).iter2.getIndex()) = 0;
            edges.get()->at((*index).iter2.getIndex()).get()->at((*index).iter1.getIndex()) = 0;
        }

        size_t getVertexesCount() const {
            return vertexes.get()->size();
        }

        size_t getEdgesCount() const {
            size_t result = 0;
            for (int i = 0; i < edges.get()->size(); ++i) {
                for (int j = i; j < edges.get()->size(); ++j) {
                    if (edges.get()->at(i).get()->at(j) != 0) result++;
                }
            }
            return result;
        }

        bool isVertexExist(const vertexIter &index) const {
            return vertexes.get()->size() > index.getIndex() && index.getIndex() > 0;
        }

        bool isVertexExist(size_t index) {
            return index < vertexes.get()->size() && index >= 0;
        }

        bool isEdgeExist(edgesIter index) {
            return edges.get()->at((*index).iter1.getIndex()).get()->at((*index).iter2.getIndex()) != 0 &&
                   edges.get()->at((*index).iter2.getIndex()).get()->at((*index).iter1.getIndex()) != 0;
        }

        bool isEdgeExist(size_t index1, size_t index2) const {
            return edges.get()->at(index1).get()->at(index2) != 0;
        }

        size_t neighborsCount(const vertexIter &index) const {
            size_t result = 0;
            for (int i = 0; i < edges.get()->size(); ++i) {
                if (edges.get()->at(index.getIndex()).get()->at(i) != 0) result++;
            }
            return result;
        }

        size_t neighborsCount(const size_t index) const {
            size_t result = 0;
            for (int i = 0; i < edges.get()->size(); ++i) {
                if (edges.get()->at(index).get()->at(i) != 0) result++;
            }
            return result;
        }

        vertexIter begin() {
            return vertexIter(vertexes, 0);
        }

        vertexIter end() {
            return vertexIter(vertexes, vertexes.get()->size());
        }

        vertexIter beginV() {
            return vertexIter(vertexes, 0);
        }

        vertexIter endV() {
            return vertexIter(vertexes, vertexes.get()->size());
        }

        constVertexIter cbeginV() const {
            return constVertexIter(vertexes, 0);
        }

        constVertexIter cendV() const {
            return constVertexIter(vertexes, vertexes.get()->size());
        }

        reverseVertexIter rbeginV() {
            return reverseVertexIter(vertexes, 0);
        }

        reverseVertexIter rendV() {
            return reverseVertexIter(vertexes, vertexes.get()->size());
        }

        edgesIter beginE() {
            return edgesIter(beginV(), beginV(), edges);
        }

        edgesIter endE() {
            return edgesIter(endV(), endV(), edges);
        }

        constEdgesIter cbeginE() const {
            return constEdgesIter(cbeginV(), cbeginV(), edges);
        }

        constEdgesIter cendE() const {
            return constEdgesIter(cendV(), cendV(), edges);
        }

        reverseEdgesIter rbeginE() {
            return reverseEdgesIter(beginV(), beginV(), edges);
        }

        reverseEdgesIter rendE() {
            return reverseEdgesIter(endV(), endV(), edges);
        }

    };
}

#endif //LABA4_GRAPH_H
