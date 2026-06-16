#pragma once
#include "ArraySequence.hpp"

template<typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(const T* data, int count) : ArraySequence<T>(data, count) {}
    ImmutableArraySequence(const DynamicArray<T>& array) : ArraySequence<T>(array) {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T>(other) {}
    ImmutableArraySequence(ImmutableArraySequence&& other) noexcept : ArraySequence<T>(std::move(other)) {}

    ImmutableArraySequence<T>& operator=(const ImmutableArraySequence<T>& other) {
        if (this != &other) {
            ArraySequence<T>::operator=(other);
        }
        return *this;
    }

    ImmutableArraySequence<T>& operator=(ImmutableArraySequence&& other) noexcept {
        if (this != &other) {
            ArraySequence<T>::operator=(std::move(other));
        }
        return *this;
    }

    ImmutableArraySequence<T>* AppendImmutable(const T& item) const {
        ImmutableArraySequence<T>* newSeq = new ImmutableArraySequence<T>(*this);
        newSeq->Append(item);
        return newSeq;
    }

    ImmutableArraySequence<T>* PrependImmutable(const T& item) const {
        ImmutableArraySequence<T>* newSeq = new ImmutableArraySequence<T>(*this);
        newSeq->Prepend(item);
        return newSeq;
    }

    ImmutableArraySequence<T>* InsertAtImmutable(const T& item, int index) const {
        if (index < 0 || index > this->GetLength()) {
            throw IndexOutOfRange(static_cast<size_t>(index), static_cast<size_t>(this->GetLength()));
        }
        ImmutableArraySequence<T>* newSeq = new ImmutableArraySequence<T>(*this);
        newSeq->InsertAt(item, index);
        return newSeq;
    }

    ImmutableArraySequence<T>* RemoveAtImmutable(int index) const {
        ImmutableArraySequence<T>* newSeq = new ImmutableArraySequence<T>(*this);
        newSeq->RemoveAt(index);
        return newSeq;
    }

    ImmutableArraySequence<T>* ClearImmutable() const {
        return new ImmutableArraySequence<T>();
    }
};