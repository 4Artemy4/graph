//
// Created by art on 11/24/20.
//
#include "Graph.h"

#ifndef LABA4_VERTEXITERATOR_H
#define LABA4_VERTEXITERATOR_H

template <typename VertexType, typename EdgesType>
class VertexIterator : public std::iterator<std::input_iterator_tag, VertexType> {

protected:
//    friend class Graph<VertexType, EdgesType>;

    std::vector<VertexType> *currentNode;
    const std::vector<VertexType> *constCurrentNode;
    size_t index = 0;

    VertexIterator(std::vector<VertexType> &node, size_t ind) {
        currentNode = &node;
        index = ind;
    }

public:
    bool operator!=(VertexIterator const &other) const {
        return index != other.index;
    };

    bool operator==(VertexIterator const &other) const {
        return index == other.index;
    }

    VertexType &operator*() {
        return currentNode->operator[](index);
    }

    VertexType *operator->() {
        return constCurrentNode->operator[](index);
    }

    virtual VertexIterator &operator++() {
        index++;
        return *this;
    }

    virtual VertexIterator &operator--() {
        index--;
        return *this;
    };
};

//    class ReverseVertexIterator : public VertexIterator {
//        ReverseVertexIterator &operator++() override {
//            VertexIterator::index++;
//            return *this;
//        }
//
//        ReverseVertexIterator &operator--() override {
//            VertexIterator::index--;
//            return *this;
//        };
//    };

#endif //LABA4_VERTEXITERATOR_H
