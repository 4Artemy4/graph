//
// Created by art on 11/29/20.
//

#ifndef LABA4_CONSTEDGESITERATOR_H
#define LABA4_CONSTEDGESITERATOR_H

#include "Graph.h"
#include "EdgesIterator.h"

namespace graph {
    template<typename NodeType, typename EdgeType>
    class ConstEdgesIterator {
    protected:
        ConstVertexIterator<NodeType> iter1;
        ConstVertexIterator<NodeType> iter2;
        vectorPtr(vectorPtr(EdgeType)) edges;

        struct Triple{
            ConstVertexIterator<NodeType> iter1;
            ConstVertexIterator<NodeType> iter2;
            const EdgeType *weight;
            Triple(ConstVertexIterator<NodeType> index1, ConstVertexIterator<NodeType> index2, EdgeType &weight):iter1(index1), iter2(index2), weight(&weight) {}
        };

    public:
        ConstEdgesIterator(ConstVertexIterator<NodeType> index1, ConstVertexIterator<NodeType> index2, vectorPtr(vectorPtr(EdgeType)) edges)
                : iter1(index1), iter2(index2), edges(edges) {};

        bool operator==(const ConstEdgesIterator &rhs) const {
            return iter1 == rhs.iter1 &&
                   iter2 == rhs.iter2;
        }

        bool operator!=(const ConstEdgesIterator &rhs) const {
            return iter1.getIndex() != rhs.iter1.getIndex() &&
                   iter2.getIndex() != rhs.iter2.getIndex();
        }

        Triple operator*() const{
            return Triple(iter1, iter2, edges.get()->at(iter1.getIndex()).get()->at(iter2.getIndex()));
        }

        ConstEdgesIterator & operator++(){
            if (iter1.getIndex() == edges.get()->size() - 1) {
                iter1.setIndex(0);
                ++iter2;
            } else ++iter1;
            return *this;
        }
        ConstEdgesIterator & operator--(){
            if (iter1.getIndex() == 0){
                iter1.setIndex(edges.get()->size()-1);
                --iter2;
            }
            else --iter1;
            return *this;
        }
    };
}


#endif //LABA4_CONSTEDGESITERATOR_H
