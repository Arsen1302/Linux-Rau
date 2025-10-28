#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <dirent.h>
#include <stdexcept>

struct DirState {
    DIR* dir;
    std::string path;
};

class RecursiveDirectoryIterator {
    std::stack<DirState> dirs;
    struct dirent* entry = nullptr;
    std::string current_path;

public:
    using value_type = std::string;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    RecursiveDirectoryIterator() = default;

    explicit RecursiveDirectoryIterator(const char* path) {
        DIR* d = opendir(path);
        if (!d) throw std::runtime_error("Cannot open directory");
        dirs.push({d, path});
        ++(*this);
    }

    ~RecursiveDirectoryIterator() {
        while (!dirs.empty()) {
            closedir(dirs.top().dir);
            dirs.pop();
        }
    }

    const std::string& operator*() const {
        return current_path;
    }

    RecursiveDirectoryIterator& operator++() {
        entry = nullptr;
        while (!dirs.empty()) {
            DIR* d = dirs.top().dir;
            entry = readdir(d);
            if (!entry) {
                closedir(d);
                dirs.pop();
                continue;
            }

            std::string name = entry->d_name;
            if (name == "." || name == "..") continue;

            current_path = dirs.top().path + "/" + name;

            if (entry->d_type == DT_DIR) {
                DIR* new_dir = opendir(current_path.c_str());
                if (new_dir) dirs.push({new_dir, current_path});
            }
            break;
        }
        return *this;
    }

    RecursiveDirectoryIterator operator++(int) {
        RecursiveDirectoryIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const RecursiveDirectoryIterator& other) const {
        return dirs.empty() && other.dirs.empty();
    }

    bool operator!=(const RecursiveDirectoryIterator& other) const {
        return !(*this == other);
    }
};
