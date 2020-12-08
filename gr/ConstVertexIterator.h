//
// Created by art on 11/29/20.
//

#ifndef LABA4_CONSTVERTEXITERATOR_H
#define LABA4_CONSTVERTEXITERATOR_H

#include <iterator>
#include "Graph.h"

namespace graph {
    template<typename NodeType>
    class ConstVertexIterator : public std::iterator<std::input_iterator_tag, NodeType> {
    protected:
        size_t index;
        vectorPtr(NodeType) vertexes;

    public:
        ConstVertexIterator(vectorPtr(NodeType) nodes, size_t ind) : vertexes(nodes), index(ind) {}

        bool operator==(const ConstVertexIterator<NodeType> &rhs) const{
            return rhs.index == index;
        }

        bool operator!=(const ConstVertexIterator<NodeType> &rhs) const{
            return rhs.index != index;
        }

        const NodeType &operator*() const {
            return vertexes->at(index);
        }

        NodeType *operator->() {
            return &vertexes.get()->at(index);
        }

        ConstVertexIterator<NodeType> &operator++() {
            index++;
            return *this;
        }

        ConstVertexIterator<NodeType> &operator--() {
            index--;
            return *this;
        }

        size_t getIndex() const {return index;}
        void setIndex(size_t ind) {index = ind;}
    };
}


#endif //LABA4_CONSTVERTEXITERATOR_H
