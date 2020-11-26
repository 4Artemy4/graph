//
// Created by art on 11/20/20.
//

#ifndef LABA4_GRAPH_H
#define LABA4_GRAPH_H

#include <vector>
#include <iostream>

template<typename Types>
struct tr {
public:
    typedef Types arg_type;
    typedef Types &reference;
    typedef Types *pointer;
};

template<typename nodeType, typename edgeType, typename traits = tr<nodeType>>
class Graph {
private:

    std::vector<nodeType> vertex;
    std::vector<std::vector<edgeType>> matrix;

    class VertexIterator : public std::iterator<std::input_iterator_tag, nodeType> {

    protected:
        friend class Graph<nodeType, edgeType>;

        std::vector<nodeType> *currentNode;
        size_t index = 0;

        VertexIterator(std::vector<nodeType> &node, size_t ind) {
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

        virtual typename tr<nodeType>::reference operator*() {
            return currentNode->at(index);
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

    class ConstVertexIterator : public std::iterator<std::input_iterator_tag, nodeType> {
    protected:
        friend class Graph<nodeType, edgeType>;

        std::vector<nodeType> *currentNode;
        size_t index = 0;

        ConstVertexIterator(std::vector<nodeType> &node, size_t ind) {
            currentNode = &node;
            index = ind;
        }

    public:
        bool operator!=(ConstVertexIterator const &other) const {
            return index != other.index;
        };

        bool operator==(ConstVertexIterator const &other) const {
            return index == other.index;
        }

        nodeType operator*() {
            return currentNode->at(index);
        }

        virtual ConstVertexIterator &operator++() {
            index++;
            return *this;
        }

        virtual ConstVertexIterator &operator--() {
            index--;
            return *this;
        };

    };

    class ReverseVertexIterator : public VertexIterator {
    public:
        ReverseVertexIterator(std::vector<nodeType> &node, size_t ind) : VertexIterator(node, ind) {}

        ReverseVertexIterator &operator++() override {
            VertexIterator::index--;
            return *this;
        };

        ReverseVertexIterator &operator--() override {
            VertexIterator::index++;
            return *this;
        }
    };

    class EdgesIterator : public std::iterator<std::input_iterator_tag, nodeType> {
    protected:
        friend class Graph<nodeType, edgeType>;

        struct Triple {
            edgeType *weight;
            VertexIterator *first;
            VertexIterator *second;

            constexpr Triple(VertexIterator &first, VertexIterator &second, edgeType &weight)
                    : first(&first),
                      second(&second),
                      weight(&weight) {};
        };

        Triple *triple;
        VertexIterator *firstIndex;
        VertexIterator *secondIndex;
        std::vector<std::vector<edgeType>> *matrix;
        std::vector<nodeType> *vertex;

        EdgesIterator(size_t index1, size_t index2, std::vector<std::vector<edgeType>> &matrix,
                      std::vector<nodeType> &vertex) {
            this->matrix = &matrix;
            this->vertex = &vertex;
            firstIndex = new VertexIterator(*this->vertex, index1);
            secondIndex = new VertexIterator(*this->vertex, index2);
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


    class ConstEdgesIterator : public std::iterator<std::input_iterator_tag, nodeType> {
    protected:
        friend class Graph<nodeType, edgeType>;

        struct Triple {
            edgeType *weight;
            VertexIterator *first;
            VertexIterator *second;

            constexpr Triple(VertexIterator &first, VertexIterator &second, edgeType &weight)
                    : first(&first),
                      second(&second),
                      weight(&weight) {};
        };

        VertexIterator *firstIndex;
        VertexIterator *secondIndex;
        std::vector<std::vector<edgeType>> *matrix;
        std::vector<nodeType> *vertex;

        ConstEdgesIterator(size_t index1, size_t index2, std::vector<std::vector<edgeType>> &matrix,
                      std::vector<nodeType> &vertex) {
            this->matrix = &matrix;
            this->vertex = &vertex;
            firstIndex = new VertexIterator(*this->vertex, index1);
            secondIndex = new VertexIterator(*this->vertex, index2);
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

    class ReverseEdgesIterator : public EdgesIterator {
        ReverseVertexIterator &operator++() override {
            if (EdgesIterator::firstIndex->index == 0) {
                EdgesIterator::secondIndex->index--;
                EdgesIterator::firstIndex->index = vertex->size() - 1;
            } else EdgesIterator::firstIndex->index--;
            return *this;
        }

        ReverseVertexIterator &operator--() override {
            if (EdgesIterator::firstIndex->index == vertex->size() - 1) {
                EdgesIterator::secondIndex->index++;
                EdgesIterator::firstIndex->index = 0;
            } else EdgesIterator::firstIndex->index++;
            return *this;
        }
    };

public:
    typedef VertexIterator vertexIterator;
    typedef ConstVertexIterator constVertexIterator;
    typedef ReverseVertexIterator reverseVertexIterator;

    typedef EdgesIterator edgesIterator;
    typedef EdgesIterator constEdgesIterator;
    typedef EdgesIterator reverseEdgesIterator;

    Graph() {};

    Graph(const size_t size) {
        matrix.resize(size);
        for (int i = 0; i < size; ++i) {
            matrix[i].resize(size);
        }
        vertex.resize(size);
    };

    Graph(const Graph &other) {
        matrix = other.matrix;
        vertex = other.vertex;
    }

    Graph &operator=(const Graph &other) {
        vertex = other.vertex;
        matrix = other.matrix;
        return *this;
    }

    bool operator==(const Graph &other) {
        return matrix == other.matrix && vertex == other.vertex;
    }

    bool operator!=(const Graph &other) {
        return !(*this == other);
    }

    friend std::ostream &operator<<(std::ostream &os, Graph &graph){
        for (auto i = graph.beginE(); i != graph.endE(); ++i) {
            os << *(*(*i).first) << "   " << *(*(*i).second) << "   " << *((*i).weight) << '\n';
        }
        std::cout << *(*(*graph.endE()).first) << "   " << *(*(*graph.endE()).second) << "   " << *((*graph.endE()).weight) << '\n';
        return os;
    }

    size_t getVertexCount() const { return vertex.size(); }

    size_t getEdgesCount() const {
        size_t result = 0;
        for (int i = 0; i < vertex.size(); ++i) {
            for (int j = i; j < vertex.size(); ++j) {
                if (matrix[i][j] != 0) result++;
            }
        }
        return result;
    };

    void addVertex(nodeType data) {
        vertex.push_back(data);
        for (auto &i : matrix) {
            i.push_back(0);
        }
        matrix.push_back(std::vector<size_t>(vertex.size()));
    };

    void addEdge(const size_t vertex1, const size_t vertex2, size_t weight) {
        matrix[vertex1][vertex2] = weight;
        matrix[vertex2][vertex1] = weight;
    };

    bool isVertexExists(const size_t index) {
        if (index >= 0 && index < matrix.size()) return true;
        return false;
    };

    bool isEdgeExists(const size_t index1, const size_t index2) {
        if (matrix[index1][index2] != 0) return true;
        return false;
    };

    void removeVertex(const size_t index) {
        vertex.erase(vertex.begin() + index);
        matrix.erase(matrix.begin() + index);
        for (auto &i: matrix) {
            i.erase(i.begin() + index);
        }
    };

    void removeVertex(const vertexIterator index) {
        removeVertex(index.index);
    };

    void removeEdge(const size_t index1, const size_t index2) {
        matrix[index1][index2] = 0;
    };

    void removeEdge(const edgesIterator iterator) {
        matrix[iterator.index1][iterator.index2] = 0;
    };

    size_t neighborsCount(size_t index) {
        size_t result = 0;
        for (int i = 0; i < vertex.size(); ++i) {
            if (matrix[index][i] != 0) result++;
        }
        return result;
    }

    bool empty() const { return vertex.empty(); }

    void clear() {
        vertex.clear();
        matrix.clear();
    }

    vertexIterator begin() { return vertexIterator(vertex, 0); }

    vertexIterator end() { return vertexIterator(vertex, vertex.size()); }

    vertexIterator beginV() { return vertexIterator(vertex, 0); }

    vertexIterator endV() { return vertexIterator(vertex, vertex.size() - 1); }

    constVertexIterator cbeginV() { return constVertexIterator(vertex, 0); }

    constVertexIterator cendV() { return constVertexIterator(vertex, vertex.size() - 1); };

    reverseVertexIterator rBeginV() { return reverseVertexIterator(vertex, 0); }

    reverseVertexIterator rEndV() { return reverseVertexIterator(vertex, vertex.size() - 1); }

    edgesIterator beginE() { return edgesIterator(0, 0, matrix, vertex); }

    edgesIterator endE() { return edgesIterator(vertex.size() - 1, vertex.size() - 1, matrix, vertex); }

    constEdgesIterator cbeginE() { return constEdgesIterator(0, 0); }

    constEdgesIterator cendE() { return constEdgesIterator(vertex.size(), vertex.size() - 1); };

    reverseEdgesIterator rbeginE() { return reverseEdgesIterator(0, 0, matrix, vertex); };

    reverseEdgesIterator rendE() { return reverseEdgesIterator(vertex.size() - 1, vertex.size() - 1, matrix, vertex); };

};


#endif //LABA4_GRAPH_H
