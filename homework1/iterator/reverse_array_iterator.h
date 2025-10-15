#pragma once
#include <cstddef>
#include <iterator>

class reverse_array_iterator {
public:
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    reverse_array_iterator(pointer current) : current_(current) {}

    reference operator*() const { return *current_; }
    pointer operator->() const { return current_; }

    reverse_array_iterator& operator++() {
        --current_;
        return *this;
    }

    reverse_array_iterator operator++(int) {
        reverse_array_iterator tmp = *this;
        --current_;
        return tmp;
    }

    bool operator==(const reverse_array_iterator& other) const {
        return current_ == other.current_;
    }

    bool operator!=(const reverse_array_iterator& other) const {
        return !(*this == other);
    }

private:
    pointer current_;
};


class reverse_array_iterator_builder {
public:
    reverse_array_iterator_builder(int* arr, size_t size)
            : arr_(arr), size_(size) {}

    reverse_array_iterator begin() {
        return reverse_array_iterator(arr_ + size_ - 1);
    }

    reverse_array_iterator end() {
        return reverse_array_iterator(arr_ - 1);
    }

private:
    int* arr_;
    size_t size_;
};
