#pragma once
#include "argument.h"
#include <string>
#include <vector>
#include <unordered_map>

class argument_parser {
public:
    using iterator = std::vector<argument>::const_iterator;

    argument_parser(char* const* args, size_t argc, std::string_view opt_string);

     iterator begin() const { return m_arguments.begin(); }
     iterator end() const { return m_arguments.end(); }

private:
    std::vector<argument> m_arguments;
    std::unordered_map<char, bool> m_option_requires_value;
};
