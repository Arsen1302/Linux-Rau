#include <filesystem>
#include <iostream>
#include <string>
#include "util/iterator/recursive_directory_iterator.h"

int main() {
    try {
        RecursiveDirectoryIterator your_it(".");
        RecursiveDirectoryIterator your_end_it;

        namespace fs = std::filesystem;
        fs::recursive_directory_iterator it(".");
        fs::recursive_directory_iterator end;

        while (it != end && your_it != your_end_it) {
            const bool same_path = it->path().string() == *your_it;
            std::cout << std::boolalpha;
            std::cout << it->path() << ": " << (same_path ? "ok" : "fail") << "\n";

            if (!same_path) {
                std::cerr << "Mismatch found!\n";
                return EXIT_FAILURE;
            }

            ++it;
            ++your_it;
        }

        if (it == end && your_it == your_end_it) {
            std::cout << "Tests have passed!\n";
            return EXIT_SUCCESS;
        } else {
            std::cerr << "Fail: Iterators ended at different times!\n";
            return EXIT_FAILURE;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
