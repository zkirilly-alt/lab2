#pragma once
#include <stdexcept>

template<typename T>
class Option {
private:
    bool hasValue;
    T value;
    
public:
    Option() : hasValue(false) {}
    
    Option(const T& val) : hasValue(true), value(val) {}
    
    static Option<T> Some(const T& val) {
        return Option<T>(val);
    }
    
    static Option<T> None() {
        return Option<T>();
    }
    
    bool IsSome() const {
        return hasValue;
    }
    
    bool IsNone() const {
        return !hasValue;
    }
    
    T Get() const {
        if (!hasValue) {
            throw std::runtime_error("Option: no value");
        }
        return value;
    }
    
    T GetOrElse(const T& defaultValue) const {
        return hasValue ? value : defaultValue;
    }
};