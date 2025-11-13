#include <iostream>
#include <cstring>
#include "util/io/serialization.h"

struct Person {
    int age;
    double height;
    char name[32];
};

static_assert(std::is_trivially_copyable_v<Person>);

int main() {
    Person p1{25, 1.82, "Arsen"};
    const std::string filename = "person.bin";

    try {
        io::serialize(p1, filename);
        Person p2 = io::deserialize<Person>(filename);

        bool equal = std::memcmp(&p1, &p2, sizeof(Person)) == 0;

        std::cout << "Deserialized object is "
                  << (equal ? "IDENTICAL" : "DIFFERENT") << std::endl;

        if (equal) {
            std::cout << "✅ Serialization/Deserialization successful!" << std::endl;
        } else {
            std::cout << "❌ Data mismatch detected." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
