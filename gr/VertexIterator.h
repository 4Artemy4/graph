//
// Created by art on 11/28/20.
//

#ifndef LABA4_VERTEXITERATOR_H
#define LABA4_VERTEXITERATOR_H
namespace graph {
    template<typename NodeType>
    class VertexIterator : public std::iterator<std::input_iterator_tag, NodeType> {
    protected:
        size_t index;
        vectorPtr(NodeType) vertexes;

    public:
        VertexIterator(vectorPtr(NodeType) nodes, size_t ind) : vertexes(nodes), index(ind) {}

        bool operator==(const VertexIterator<NodeType> &rhs) const {
            return index == rhs.index;
        }

        bool operator!=(const VertexIterator<NodeType> &rhs) const {
            return index != rhs.index;
        }
        bool operator<(const VertexIterator<NodeType> &rhs) const {
            return index < rhs.index;
        }
        bool operator>(const VertexIterator<NodeType> &rhs) const {
            return index > rhs.index;
        }

        NodeType &operator*() {
            return vertexes->at(index);
        }

        NodeType *operator->() {
            return &vertexes.get()->at(index);
        }

        virtual VertexIterator<NodeType> &operator++() {
            index++;
            return *this;
        }

        virtual VertexIterator<NodeType> &operator--() {
            index--;
            return *this;
        }

        size_t getIndex() const { return index; }
        void setIndex(size_t ind) {index = ind; }
    };
}


#endif //LABA4_VERTEXITERATOR_H
