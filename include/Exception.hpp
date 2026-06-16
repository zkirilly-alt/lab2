#pragma once
#include <exception>
#include <string>

class Exception : public std::exception {
protected:
    std::string error;
public:
    Exception(const char* message) : error(message) {}
    Exception(const std::string& message) : error(message) {}
    virtual ~Exception() = default;
    const char* what() const noexcept override { return error.c_str(); }
};

class IndexOutOfRange : public Exception {
private:
    size_t index;
    size_t size;
    bool hasDetails;
public:
    IndexOutOfRange(const char* message) : Exception(message), index(0), size(0), hasDetails(false) {}
    IndexOutOfRange(const std::string& message) : Exception(message), index(0), size(0), hasDetails(false) {}
    IndexOutOfRange(size_t idx, size_t sz) : Exception(""), index(idx), size(sz), hasDetails(true) {}
    IndexOutOfRange(int idx, size_t sz) : Exception(""), index(static_cast<size_t>(idx)), size(sz), hasDetails(true) {}
    bool HasDetails() const { return hasDetails; }
    size_t GetIndex() const { return index; }
    size_t GetSize() const { return size; }
};

class EmptyContainerError : public Exception {
public:
    EmptyContainerError(const char* message) : Exception(message) {}
    EmptyContainerError(const std::string& message) : Exception(message) {}
};

class InvalidArgumentError : public Exception {
public:
    InvalidArgumentError(const char* message) : Exception(message) {}
    InvalidArgumentError(const std::string& message) : Exception(message) {}
};

class NullPtrException : public Exception {
public:
    NullPtrException(const char* message) : Exception(message) {}
    NullPtrException(const std::string& message) : Exception(message) {}
};

class LengthMismatchException : public Exception {
public:
    LengthMismatchException(const char* message) : Exception(message) {}
    LengthMismatchException(const std::string& message) : Exception(message) {}
};