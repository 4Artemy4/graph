//
// Created by art on 11/29/20.
//

#ifndef LABA4_REVERSEVERTEXITERATOR_H
#define LABA4_REVERSEVERTEXITERATOR_H

#include "Graph.h"

namespace graph {
    template<typename NodeType>
    class ReverseVertexIterator : public VertexIterator<NodeType> {
        typedef VertexIterator<NodeType> parent;
    public:
        ReverseVertexIterator(vectorPtr(NodeType) nodes, size_t ind) : parent(nodes, ind) {}

        VertexIterator<NodeType> &operator++() override{
            parent::index--;
            return *this;
        }

        VertexIterator<NodeType> &operator--() override{
            parent::index++;
            return *this;
        }
    };
}
#endif //LABA4_REVERSEVERTEXITERATOR_H
