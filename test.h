#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

template<typename T>
class fixed_array {
public:

    typedef int size_type;

    class iterator {
    public:
        typedef iterator self_type;

        iterator(T* ptr) : ptr_(ptr) {}

        self_type operator++() {
            return ptr_++;
        }

        T& operator*() { return *ptr_; }

        T* operator->() { return ptr_; }

        bool operator==(const self_type &rhs) { return ptr_ == rhs.ptr_; }

        bool operator!=(const self_type &rhs) { return ptr_ != rhs.ptr_; }

    private:
        T* ptr_;
    };

    explicit fixed_array(size_type size) : size_(size) { data_ = new T[size_]; }

    size_type size() const { return size_; }

    T &operator[](size_type index) { return data_[index]; }

    const T &operator[](size_type index) const { return data_[index]; }

    iterator begin() { return iterator(data_); }

    iterator end() { return iterator(data_ + size_); }

    iterator cbegin() const { return iterator(data_); }

    iterator cend() const { return iterator(data_ + size_); }

private:
    T *data_;
    size_type size_;
};


//int main() {
//    fixed_array<double> point3d(4);
//    point3d[0] = 2.3;
//    point3d[1] = 3.2;
//    point3d[2] = 4.5;
//    point3d[3] = 5.6;
//
//    for (auto i = point3d.begin(); i != point3d.end(); ++i) {
//        std::cout << &i << "\n";
//    }
//
//    auto b = point3d.cbegin();
//    *b = 7;
//
//    return 0;
//}