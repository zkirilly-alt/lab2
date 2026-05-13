#pragma once
#include "exceptions.hpp"
#include <cstddef>
#include <algorithm>

template<typename T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;
    
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        size_t copySize = std::min(size, newCapacity);
        for (size_t i = 0; i < copySize; ++i) {
            newData[i] = data[i];
        }
        for (size_t i = copySize; i < newCapacity; ++i) {
            newData[i] = T();
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
        if (size > newCapacity) {
            size = newCapacity;
        }
    }

public:
    DynamicArray() : data(nullptr), size(0), capacity(0) {}
    
    explicit DynamicArray(size_t size) : data(new T[size]()), size(size), capacity(size) {}
    
    DynamicArray(const T* items, size_t count) : data(new T[count]), size(count), capacity(count) {
        for (size_t i = 0; i < count; ++i) {
            data[i] = items[i];
        }
    }
    
    DynamicArray(const DynamicArray& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
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
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
    
    T& Get(size_t index) {
        if (index >= size) {
            throw IndexOutOfRange("DynamicArray::Get: index out of range");
        }
        return data[index];
    }
    
    const T& Get(size_t index) const {
        if (index >= size) {
            throw IndexOutOfRange("DynamicArray::Get: index out of range");
        }
        return data[index];
    }
    
    void Set(size_t index, const T& value) {
        if (index >= size) {
            throw IndexOutOfRange("DynamicArray::Set: index out of range");
        }
        data[index] = value;
    }
    
    size_t GetSize() const { return size; }
    size_t GetCapacity() const { return capacity; }
    
    void Append(const T& value) {
        if (size >= capacity) {
            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
            resize(newCapacity);
        }
        data[size++] = value;
    }
    
    void Resize(size_t newSize) {
        if (newSize > capacity) {
            resize(newSize);
        }
        size = newSize;
    }
    
    void Clear() {
        size = 0;
    }
};