#pragma once
#include "Exception.hpp"
#include <cstddef>

template<typename T>
class Sequence {
public:
    virtual ~Sequence() = default;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;

    virtual void Append(const T& item) = 0;
    virtual void Prepend(const T& item) = 0;
    virtual void InsertAt(const T& item, int index) = 0;
    virtual Sequence<T>* Concat(const Sequence<T>& other) const = 0;
    virtual void RemoveAt(int index) = 0;
    virtual void Clear() = 0;
};  