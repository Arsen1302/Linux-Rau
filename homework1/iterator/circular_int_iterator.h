#pragma once
#include <cstddef>

class circular_int_iterator_builder {
public:
    circular_int_iterator_builder(int* data, size_t size)
            : data_(data), size_(size), current_(0) {}

    int& operator*() { return data_[current_]; }

    circular_int_iterator_builder& operator++() {
        current_ = (current_ + 1) % size_;
        return *this;
    }

private:
    int* data_;
    size_t size_;
    size_t current_;
};
