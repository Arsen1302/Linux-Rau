#include "../include/argumentParser.h"
#include <string>

argument_parser::argument_parser(char* const* args, size_t argc, std::string_view opt_string) {
    for (size_t i = 0; i < opt_string.size(); ++i) {
        char c = opt_string[i];
        if (c == ':') continue;
        bool requires_value = (i + 1 < opt_string.size() && opt_string[i + 1] == ':');
        m_option_requires_value[c] = requires_value;
    }

    for (size_t i = 1; i < argc; ++i) {
        char* arg = args[i];

        if (arg[0] == '-' && arg[1] != '\0') {
            char opt_char = arg[1];
            auto it = m_option_requires_value.find(opt_char);
            if (it != m_option_requires_value.end()) {
                if (it->second) {
                    if (i + 1 < argc) {
                        m_arguments.emplace_back(std::string(arg), std::string(args[i + 1]));
                        ++i;
                    } else {
                        m_arguments.emplace_back(std::string(arg), argument_type::unknown);
                    }
                } else {
                    m_arguments.emplace_back(std::string(arg), argument_type::flag);
                }
            } else {
                m_arguments.emplace_back(std::string(arg), argument_type::unknown);
            }
        } else {
            m_arguments.emplace_back(std::string(arg), argument_type::positional);
        }
    }
}


#include <iostream>


int main(int argc, char* argv[]) {
    argument_parser parser(argv, argc, "vo:");

    for (const auto& arg : parser) {
        std::cout << arg.string() << " | Type: ";
        if (arg.is_flag()) std::cout << "FLAG";
        else if (arg.is_option()) std::cout << "OPTION";
        else if (arg.is_positional()) std::cout << "POSITIONAL";
        else std::cout << "UNKNOWN";
        std::cout << std::endl;
    }
}
