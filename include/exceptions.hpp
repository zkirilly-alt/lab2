#pragma once
#include <stdexcept>
#include <string>

class IndexOutOfRange : public std::out_of_range {
public:
    explicit IndexOutOfRange(const std::string& msg = "Index out of range")
        : std::out_of_range(msg) {}
};

class EmptyContainerError : public std::runtime_error {
public:
    explicit EmptyContainerError(const std::string& msg = "Container is empty")
        : std::runtime_error(msg) {}
};

class InvalidArgumentError : public std::invalid_argument {
public:
    explicit InvalidArgumentError(const std::string& msg = "Invalid argument")
        : std::invalid_argument(msg) {}
};