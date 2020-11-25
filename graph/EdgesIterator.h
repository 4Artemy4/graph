//
// Created by art on 11/24/20.
//

#ifndef LABA4_EDGESITERATOR_H
#define LABA4_EDGESITERATOR_H
#include "Graph.h"
#include "VertexIterator.h"

template <typename VertexType, typename EdgesType>

class EdgesIterator : public std::iterator<std::input_iterator_tag, EdgesType> {
protected:
//    friend class Graph<VertexType, EdgesType>;

    struct Triple {
        EdgesType weight;
        VertexIterator<VertexType, EdgesType> *first;
        VertexIterator<VertexType, EdgesType> *second;

        constexpr Triple(VertexIterator<VertexType, EdgesType> &first, VertexIterator<VertexType, EdgesType> &second, const EdgesType weight) : first(&first),
                                                                                                                                                second(&second),
                                                                                                                                                weight(weight) {};
    };

    VertexIterator<VertexType, EdgesType> *firstIndex;
    VertexIterator<VertexType, EdgesType> *secondIndex;
    std::vector<std::vector<EdgesType>> *matrix;
    std::vector<VertexType> *vertex;

    EdgesIterator(size_t index1, size_t index2, std::vector<std::vector<EdgesType>> &matrix, std::vector<VertexType> &vertex) {
        this->matrix = &matrix;
        this->vertex = &vertex;
        firstIndex = new VertexIterator<VertexType, EdgesType>(*this->vertex, index1);
        secondIndex = new VertexIterator<VertexType, EdgesType>(*this->vertex, index2);
    }

public:

    bool operator==(EdgesIterator const &other) const {
        return firstIndex == other.firstIndex && secondIndex == other.secondIndex;
    }

    Triple operator*() const {
        return Triple(*firstIndex, *secondIndex, matrix->at(firstIndex->index).at(secondIndex->index));
    }

    bool operator!=(EdgesIterator const &other) const {
        return firstIndex->index != other.firstIndex->index || secondIndex->index != other.secondIndex->index;
    }

    virtual EdgesIterator &operator++() {
        if (firstIndex->index == vertex->size() - 1) {
            secondIndex->index++;
            firstIndex->index = 0;
        } else firstIndex->index++;
        return *this;
    }

    virtual EdgesIterator &operator--() {
        if (firstIndex->index == 0) {
            secondIndex->index--;
            firstIndex->index = vertex->size() - 1;
        } else firstIndex->index--;
        return *this;
    }
};

//class ReverseEdgesIterator : public EdgesIterator {
//    ReverseVertexIterator &operator++() override {
//        if (EdgesIterator::firstIndex->index == 0) {
//            EdgesIterator::secondIndex->index--;
//            EdgesIterator::firstIndex->index = vertex->size() - 1;
//        } else EdgesIterator::firstIndex->index--;
//        return *this;
//    }
//
//    ReverseVertexIterator &operator--() override {
//        if (EdgesIterator::firstIndex->index == vertex->size() - 1) {
//            EdgesIterator::secondIndex->index++;
//            EdgesIterator::firstIndex->index = 0;
//        } else EdgesIterator::firstIndex->index++;
//        return *this;
//    }
//};
#endif //LABA4_EDGESITERATOR_H
