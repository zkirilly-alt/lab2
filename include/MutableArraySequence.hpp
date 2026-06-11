#pragma once
#include "ArraySequence.hpp"

template<typename T>
class MutableArraySequence : public ArraySequence<T> {
public:
    MutableArraySequence() : ArraySequence<T>() {}

    MutableArraySequence(const T* data, int count) : ArraySequence<T>(data, count) {}

    MutableArraySequence(const DynamicArray<T>& array) : ArraySequence<T>(array) {}

    MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequence<T>(other) {}

    void AppendMutable(const T& item) {
        this->Append(item);
    }

    void PrependMutable(const T& item) {
        this->Prepend(item);
    }

    void InsertAtMutable(const T& item, int index) {
        this->InsertAt(item, index);
    }

    void RemoveAtMutable(int index) {
        this->RemoveAt(index);
    }

    void ClearMutable() {
        this->Clear();
    }
};