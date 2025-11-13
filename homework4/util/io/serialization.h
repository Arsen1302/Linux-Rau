#pragma once
#include <string>
#include <cstring>
#include <type_traits>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>

namespace io {

    template <typename T>
    void serialize(const T& obj, const std::string& filename) {
        static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

        int fd = open(filename.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
        if (fd == -1)
            throw std::runtime_error("Failed to open file for writing");

        if (ftruncate(fd, sizeof(T)) == -1) {
            close(fd);
            throw std::runtime_error("Failed to resize file");
        }

        void* map = mmap(nullptr, sizeof(T), PROT_WRITE, MAP_SHARED, fd, 0);
        if (map == MAP_FAILED) {
            close(fd);
            throw std::runtime_error("Failed to mmap file for writing");
        }

        std::memcpy(map, &obj, sizeof(T));

        msync(map, sizeof(T), MS_SYNC);
        munmap(map, sizeof(T));
        close(fd);
    }

    template <typename T>
    T deserialize(const std::string& filename) {
        static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

        int fd = open(filename.c_str(), O_RDONLY);
        if (fd == -1)
            throw std::runtime_error("Failed to open file for reading");

        struct stat st{};
        if (fstat(fd, &st) == -1) {
            close(fd);
            throw std::runtime_error("Failed to get file info");
        }

        if (st.st_size != sizeof(T)) {
            close(fd);
            throw std::runtime_error("File size does not match object size");
        }

        void* map = mmap(nullptr, sizeof(T), PROT_READ, MAP_PRIVATE, fd, 0);
        if (map == MAP_FAILED) {
            close(fd);
            throw std::runtime_error("Failed to mmap file for reading");
        }

        T obj;
        std::memcpy(&obj, map, sizeof(T));

        munmap(map, sizeof(T));
        close(fd);

        return obj;
    }

}
