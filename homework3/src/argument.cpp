#include "../include/argument.h"

argument::argument()
        : m_type(argument_type::unknown) {}

argument::argument(std::string name, argument_type type)
        : m_name(std::move(name)), m_type(type) {}

argument::argument(std::string name, std::string value)
        : m_name(std::move(name)), m_value(std::move(value)), m_type(argument_type::option) {}

argument_type argument::type() const noexcept {
    return m_type;
}

const std::string& argument::name() const noexcept {
    return m_name;
}

const std::string& argument::value() const noexcept {
    return m_value;
}

bool argument::has_value() const noexcept {
    return !m_value.empty();
}

bool argument::is_flag() const noexcept {
    return m_type == argument_type::flag;
}

bool argument::is_option() const noexcept {
    return m_type == argument_type::option;
}

bool argument::is_positional() const noexcept {
    return m_type == argument_type::positional;
}

std::string argument::string() const {
    std::ostringstream out;
    out << m_name;
    if (has_value())
        out << "=" << m_value;
    return out.str();
}


#include <iostream>
#include <vector>

int main() {
    std::vector<argument> args = {
            argument("-v", argument_type::flag),
            argument("-O", "3"),
            argument("main.cpp", argument_type::positional)
    };

    for (const auto& arg : args) {
        std::cout << "Name: " << arg.name()
                  << ", Type: ";
        if (arg.is_flag()) std::cout << "FLAG";
        else if (arg.is_option()) std::cout << "OPTION";
        else if (arg.is_positional()) std::cout << "POSITIONAL";
        else std::cout << "UNKNOWN";

        if (arg.has_value()) std::cout << ", Value: " << arg.value();

        std::cout << ", String: " << arg.string() << std::endl;
    }

    return 0;
}


