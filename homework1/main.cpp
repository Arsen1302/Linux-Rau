#include <iostream>
#include <vector>
#include "iterator/circular_int_iterator.h"

int main() {
    std::vector<int> numbers = {10, 20, 30};
    circular_int_iterator_builder circular(numbers.data(), numbers.size());

    for (int i = 0; i < 7; ++i) {
        std::cout << *circular << " ";
        ++circular;
    }

    std::cout << std::endl;
}
