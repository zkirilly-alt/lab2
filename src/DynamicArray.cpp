#include "DynamicArray.hpp"

template<typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(0) {}

template<typename T>
DynamicArray<T>::DynamicArray(size_t size) 
    : data(new T[size]()), size(size), capacity(size) {}

template<typename T>
DynamicArray<T>::DynamicArray(const T* items, size_t count)
    : data(new T[count]), size(count), capacity(count) {
    for (size_t i = 0; i < count; ++i) {
        data[i] = items[i];
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
    : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
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

template<typename T>
void DynamicArray<T>::resize(size_t newCapacity) {
    T* newData = new T[newCapacity];
    size_t copySize = std::min(size, newCapacity);
    for (size_t i = 0; i < copySize; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
    if (size > newCapacity) {
        size = newCapacity;
    }
}

template<typename T>
T& DynamicArray<T>::operator[](size_t index) {
    return data[index];
}

template<typename T>
const T& DynamicArray<T>::operator[](size_t index) const {
    return data[index];
}

template<typename T>
T& DynamicArray<T>::Get(size_t index) {
    if (index >= size) {
        throw IndexOutOfRange("DynamicArray::Get: index out of range");
    }
    return data[index];
}

template<typename T>
const T& DynamicArray<T>::Get(size_t index) const {
    if (index >= size) {
        throw IndexOutOfRange("DynamicArray::Get: index out of range");
    }
    return data[index];
}

template<typename T>
void DynamicArray<T>::Set(size_t index, const T& value) {
    if (index >= size) {
        throw IndexOutOfRange("DynamicArray::Set: index out of range");
    }
    data[index] = value;
}

template<typename T>
void DynamicArray<T>::Append(const T& value) {
    if (size >= capacity) {
        size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
        resize(newCapacity);
    }
    data[size++] = value;
}

template<typename T>
void DynamicArray<T>::Resize(size_t newSize) {
    if (newSize > capacity) {
        resize(newSize);
    }
    size = newSize;
}

template<typename T>
void DynamicArray<T>::Clear() {
    size = 0;
}

// Явная инстанциация
template class DynamicArray<int>;
template class DynamicArray<double>;
template class DynamicArray<bool>;