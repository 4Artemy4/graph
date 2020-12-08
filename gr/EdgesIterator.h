//
// Created by art on 11/28/20.
//

#ifndef LABA4_EDGESITERATOR_H
#define LABA4_EDGESITERATOR_H

namespace graph {
    template<typename NodeType, typename EdgeType>
    class EdgesIterator {
    protected:
        VertexIterator<NodeType> iter1;
        VertexIterator<NodeType> iter2;
        vectorPtr(vectorPtr(EdgeType)) edges;

        struct Triple{
            VertexIterator<NodeType> iter1;
            VertexIterator<NodeType> iter2;
            EdgeType *weight;
            Triple(VertexIterator<NodeType> index1, VertexIterator<NodeType> index2, EdgeType &weight):iter1(index1), iter2(index2), weight(&weight) {}
        };

    public:
        EdgesIterator(VertexIterator<NodeType> index1, VertexIterator<NodeType> index2, vectorPtr(vectorPtr(EdgeType)) edges)
                : iter1(index1), iter2(index2), edges(edges) {};

        bool operator==(const EdgesIterator &rhs) const {
            return iter1 == rhs.iter1 &&
                   iter2 == rhs.iter2;
        }

        bool operator!=(const EdgesIterator &rhs) const {
            return iter1.getIndex() != rhs.iter1.getIndex() &&
                   iter2.getIndex() != rhs.iter2.getIndex();
        }

        Triple operator*(){
            return Triple(iter1, iter2, edges.get()->at(iter1.getIndex()).get()->at(iter2.getIndex()));
        }

        virtual EdgesIterator & operator++(){
                if (iter1.getIndex() == edges.get()->size() - 1) {
                    iter1.setIndex(0);
                    ++iter1;
                } else ++iter1;
            return *this;
        }

        virtual EdgesIterator & operator++(int){
                if (iter1.getIndex() == edges.get()->size() - 1) {
                    iter1.setIndex((++iter2).getIndex());
                    ++iter1;
                } else ++iter1;
            return *this;
        }

        virtual EdgesIterator & operator--(){
            if (iter1.getIndex() == 0){
                iter1.setIndex(edges.get()->size()-1);
                --iter2;
            }
            else --iter1;
            return *this;
        }
    };
}


#endif //LABA4_EDGESITERATOR_H
