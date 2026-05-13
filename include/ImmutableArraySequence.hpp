#pragma once
#include "ArraySequence.hpp"

template<typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    
    ImmutableArraySequence(const T* data, int count) : ArraySequence<T>(data, count) {}
    
    ImmutableArraySequence(const DynamicArray<T>& array) : ArraySequence<T>(array) {}
    
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T>(other) {}
    
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
        ImmutableArraySequence<T>* newSeq = new ImmutableArraySequence<T>(*this);
        newSeq->InsertAt(item, index);
        return newSeq;
    }
};