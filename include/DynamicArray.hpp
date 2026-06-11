#pragma once
#include "Exception.hpp"
#include <cstddef>
#include <algorithm>

template<typename T>
class DynamicArray {
private:
    T* data;
    size_t size;

    void allocate(size_t newSize) {
        T* newData = new T[newSize]();
        if (data) {
            size_t copySize = std::min(size, newSize);
            for (size_t i = 0; i < copySize; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
        }
        data = newData;
        size = newSize;
    }

public:
    DynamicArray() : data(nullptr), size(0) {}

    explicit DynamicArray(size_t size) : data(new T[size]()), size(size) {}

    DynamicArray(const T* items, size_t count) : data(new T[count]), size(count) {
        for (size_t i = 0; i < count; ++i) {
            data[i] = items[i];
        }
    }

    DynamicArray(const DynamicArray& other) : data(new T[other.size]), size(other.size) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            if (size > 0) {
                data = new T[size];
                for (size_t i = 0; i < size; ++i) {
                    data[i] = other.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    T& operator[](size_t index) {
        if (index >= size) throw IndexOutOfRange(index, size);
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw IndexOutOfRange(index, size);
        return data[index];
    }

    T& Get(size_t index) {
        if (index >= size) throw IndexOutOfRange(index, size);
        return data[index];
    }

    const T& Get(size_t index) const {
        if (index >= size) throw IndexOutOfRange(index, size);
        return data[index];
    }

    void Set(size_t index, const T& value) {
        if (index >= size) throw IndexOutOfRange(index, size);
        data[index] = value;
    }

    size_t GetSize() const { return size; }

    void Append(const T& value) {
        allocate(size + 1);
        data[size - 1] = value;
    }

    void Resize(size_t newSize) {
        if (newSize == size) return;
        allocate(newSize);
    }

    void Clear() {
        delete[] data;
        data = nullptr;
        size = 0;
    }

    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++ptr; return tmp; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    class ConstIterator {
    private:
        const T* ptr;
    public:
        ConstIterator(const T* p) : ptr(p) {}
        const T& operator*() const { return *ptr; }
        ConstIterator& operator++() { ++ptr; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++ptr; return tmp; }
        bool operator==(const ConstIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }
    ConstIterator begin() const { return ConstIterator(data); }
    ConstIterator end() const { return ConstIterator(data + size); }
};
