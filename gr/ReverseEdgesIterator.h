//
// Created by art on 11/29/20.
//

#ifndef LABA4_REVERSEEDGESITERATOR_H
#define LABA4_REVERSEEDGESITERATOR_H

#include "EdgesIterator.h"
#include "Graph.h"

namespace graph {
    template<typename NodeType, typename EdgeType>
    class ReverseEdgesIterator : public graph::EdgesIterator<NodeType, EdgeType> {
        typedef EdgesIterator<NodeType, EdgeType> parent;
    public:
        ReverseEdgesIterator(VertexIterator<NodeType> index1, VertexIterator<NodeType> index2,
                             vectorPtr(vectorPtr(EdgeType)) edges) : parent(index1, index2, edges) {}

        ReverseEdgesIterator &operator++() override {
            if (parent::iter1.getIndex() == 0) {
                parent::iter1.setIndex(parent::edges.get()->size() - 1);
                --parent::iter2;
            } else --parent::iter1;
            return *this;
        }

        ReverseEdgesIterator &operator--() override {
            if (parent::iter1.getIndex() == parent::edges.get()->size() - 1) {
                parent::iter1.setIndex(0);
                ++parent::iter2;
            } else ++parent::iter1;
            return *this;
        }
    };
}
#endif //LABA4_REVERSEEDGESITERATOR_H
