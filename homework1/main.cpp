#include <iostream>
#include <vector>
#include "iterator/filter_integer_iterator.h"

bool is_even(int num) {
    return num % 2 == 0;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6,7,8,20};
    filter_integer_iterator_builder even_iter(numbers.data(), numbers.size(), is_even);

    for (int & it : even_iter) {
        std::cout << it << " ";
    }

    return 0;
}