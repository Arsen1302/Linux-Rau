#pragma once
#include <cstddef>
#include <functional>

template<typename Predicate>
class filter_integer_iterator {
public:
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    filter_integer_iterator(pointer ptr, pointer end, Predicate pred)
            : current_(ptr), end_(end), pred_(pred) {
        advance_to_valid();
    }

    reference operator*() const { return *current_; }
    pointer operator->() const { return current_; }

    filter_integer_iterator& operator++() {
        ++current_;
        advance_to_valid();
        return *this;
    }

    filter_integer_iterator operator++(int) {
        filter_integer_iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const filter_integer_iterator& other) const {
        return current_ == other.current_;
    }

    bool operator!=(const filter_integer_iterator& other) const {
        return !(*this == other);
    }

private:
    void advance_to_valid() {
        while (current_ != end_ && !pred_(*current_)) {
            ++current_;
        }
    }

    pointer current_;
    pointer end_;
    Predicate pred_;
};


template<typename Predicate>
class filter_integer_iterator_builder {
public:
    filter_integer_iterator_builder(int* data, std::size_t size, Predicate pred)
            : data_(data), size_(size), pred_(pred) {}

    auto begin() { return filter_integer_iterator<Predicate>(data_, data_ + size_, pred_); }
    auto end()   { return filter_integer_iterator<Predicate>(data_ + size_, data_ + size_, pred_); }

private:
    int* data_;
    std::size_t size_;
    Predicate pred_;
};
