#pragma once
#include <string>
#include <sstream>


enum class argument_type {
    unknown,
    flag,
    option,
    positional
};

class argument {
public:
    argument();
    argument(std::string name, argument_type type);
    argument(std::string name, std::string value);

    argument_type type() const noexcept;
    const std::string& name() const noexcept;
    const std::string& value() const noexcept;

    bool is_flag() const noexcept;
    bool is_option() const noexcept;
    bool is_positional() const noexcept;
    bool has_value() const noexcept;

    std::string string() const;

private:
    std::string m_name;
    std::string m_value;
    argument_type m_type;
};
