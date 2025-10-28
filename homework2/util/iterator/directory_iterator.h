#include <iterator>
#include <cstddef>
#include <dirent.h>


class SimpleForwardIterator {
    DIR* dir = nullptr;
    struct dirent* entry = nullptr;
public:
    using difference_type = std::ptrdiff_t;
    using value_type = const char*;
    using iterator_category = std::forward_iterator_tag;

    SimpleForwardIterator() = default;

    SimpleForwardIterator(const char* path) {
        dir = opendir(path);
        if (!dir) {
            throw std::runtime_error("Cannot open directory");
        }
        entry = readdir(dir);
    }

    ~SimpleForwardIterator() {
        if (dir) closedir(dir);
    }

    SimpleForwardIterator(const SimpleForwardIterator&) = default;
    SimpleForwardIterator& operator=(const SimpleForwardIterator&) = default;

    const char* operator*() const {
        return entry->d_name;
    }

    SimpleForwardIterator& operator++() {
        if (dir) {
            entry = readdir(dir);
            if (!entry) {
                closedir(dir);
                dir = nullptr;
            }
        }
        return *this;
    }

    SimpleForwardIterator operator++(int) {
        SimpleForwardIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const SimpleForwardIterator& other) const {
        return entry == other.entry;
    }

    bool operator!=(const SimpleForwardIterator& other) const {
        return !(*this == other);
    }
};
