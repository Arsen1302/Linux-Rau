#include <iostream>


bool is_booted() {
    bool running = true;

    if (running) {
        return true;
    }

    while (true) { };
}


int main () {

    std::cout << is_booted()<< std::endl;

    return 0;
}