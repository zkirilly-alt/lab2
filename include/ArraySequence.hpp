#pragma once
#include "Sequence.hpp"
#include "DynamicArray.hpp"

template<typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* items;
    
    void checkIndex(int index) const {
        if (index < 0 || static_cast<size_t>(index) >= items->GetSize()) {
            throw IndexOutOfRange("ArraySequence: index out of range");
        }
    }

public:
    ArraySequence() {
        items = new DynamicArray<T>();
    }
    
    ArraySequence(const T* data, int count) {
        items = new DynamicArray<T>(data, static_cast<size_t>(count));
    }
    
    ArraySequence(const DynamicArray<T>& array) {
        items = new DynamicArray<T>(array);
    }
    
    ArraySequence(const ArraySequence<T>& other) {
        items = new DynamicArray<T>(*(other.items));
    }
    
    ~ArraySequence() {
        delete items;
    }
    
    T GetFirst() const override {
        if (items->GetSize() == 0) {
            throw EmptyContainerError("ArraySequence: sequence is empty");
        }
        return items->Get(0);
    }
    
    T GetLast() const override {
        if (items->GetSize() == 0) {
            throw EmptyContainerError("ArraySequence: sequence is empty");
        }
        return items->Get(items->GetSize() - 1);
    }
    
    T Get(int index) const override {
        checkIndex(index);
        return items->Get(static_cast<size_t>(index));
    }
    
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        checkIndex(startIndex);
        checkIndex(endIndex);
        if (startIndex > endIndex) {
            throw InvalidArgumentError("ArraySequence: start index > end index");
        }
        
        int newSize = endIndex - startIndex + 1;
        T* tempData = new T[static_cast<size_t>(newSize)];
        for (int i = 0; i < newSize; ++i) {
            tempData[i] = items->Get(static_cast<size_t>(startIndex + i));
        }
        
        ArraySequence<T>* result = new ArraySequence<T>(tempData, newSize);
        delete[] tempData;
        return result;
    }
    
    int GetLength() const override {
        return static_cast<int>(items->GetSize());
    }
    
    void Append(const T& item) override {
        items->Append(item);
    }
    
    void Prepend(const T& item) override {
        int newSize = static_cast<int>(items->GetSize()) + 1;
        T* tempData = new T[static_cast<size_t>(newSize)];
        tempData[0] = item;
        for (int i = 0; i < static_cast<int>(items->GetSize()); ++i) {
            tempData[i + 1] = items->Get(static_cast<size_t>(i));
        }
        
        delete items;
        items = new DynamicArray<T>(tempData, static_cast<size_t>(newSize));
        delete[] tempData;
    }
    
    void InsertAt(const T& item, int index) override {
        if (index < 0 || static_cast<size_t>(index) > items->GetSize()) {
            throw IndexOutOfRange("ArraySequence: insert index out of range");
        }
        
        int newSize = static_cast<int>(items->GetSize()) + 1;
        T* tempData = new T[static_cast<size_t>(newSize)];
        
        for (int i = 0; i < index; ++i) {
            tempData[i] = items->Get(static_cast<size_t>(i));
        }
        
        tempData[index] = item;
        
        for (int i = index; i < static_cast<int>(items->GetSize()); ++i) {
            tempData[i + 1] = items->Get(static_cast<size_t>(i));
        }
        
        delete items;
        items = new DynamicArray<T>(tempData, static_cast<size_t>(newSize));
        delete[] tempData;
    }
    
    Sequence<T>* Concat(const Sequence<T>& other) const override {
        ArraySequence<T>* result = new ArraySequence<T>(*this);
        
        for (int i = 0; i < other.GetLength(); ++i) {
            result->Append(other.Get(i));
        }
        
        return result;
    }
    
    DynamicArray<T>& GetInternalArray() {
        return *items;
    }
    void Clear() {
        delete items;
        items = new DynamicArray<T>();
    }
    void RemoveAt(int index) {
        checkIndex(index);
        size_t newSize = items->GetSize() - 1;
        T* tempData = new T[newSize];
        for (int i = 0; i < index; ++i) {
            tempData[i] = items->Get(i);
        }
        for (size_t i = index + 1; i < items->GetSize(); ++i) {
            tempData[i - 1] = items->Get(i);
        }
        delete items;
        items = new DynamicArray<T>(tempData, newSize);
        delete[] tempData;
    }
};