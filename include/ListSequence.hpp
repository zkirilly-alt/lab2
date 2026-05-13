#pragma once
#include "Sequence.hpp"
#include "LinkedList.hpp"

template<typename T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T>* items;
    
    void checkIndex(int index) const {
        if (index < 0 || static_cast<size_t>(index) >= items->GetLength()) {
            throw IndexOutOfRange("ListSequence: index out of range");
        }
    }

public:
    ListSequence() {
        items = new LinkedList<T>();
    }
    
    ListSequence(const T* data, int count) {
        items = new LinkedList<T>(data, static_cast<size_t>(count));
    }
    
    ListSequence(const LinkedList<T>& list) {
        items = new LinkedList<T>(list);
    }
    
    ListSequence(const ListSequence<T>& other) {
        items = new LinkedList<T>(*(other.items));
    }
    
    ~ListSequence() {
        delete items;
    }
    
    T GetFirst() const override {
        if (items->GetLength() == 0) {
            throw EmptyContainerError("ListSequence: sequence is empty");
        }
        return items->GetFirst();
    }
    
    T GetLast() const override {
        if (items->GetLength() == 0) {
            throw EmptyContainerError("ListSequence: sequence is empty");
        }
        return items->GetLast();
    }
    
    T Get(int index) const override {
        checkIndex(index);
        return items->Get(static_cast<size_t>(index));
    }
    
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        checkIndex(startIndex);
        checkIndex(endIndex);
        if (startIndex > endIndex) {
            throw InvalidArgumentError("ListSequence: start index > end index");
        }
        
        LinkedList<T> sublist = items->GetSubList(static_cast<size_t>(startIndex), static_cast<size_t>(endIndex));
        ListSequence<T>* result = new ListSequence<T>(sublist);
        return result;
    }
    
    int GetLength() const override {
        return static_cast<int>(items->GetLength());
    }
    
    void Append(const T& item) override {
        items->Append(item);
    }
    
    void Prepend(const T& item) override {
        items->Prepend(item);
    }
    
    void InsertAt(const T& item, int index) override {
        if (index < 0 || static_cast<size_t>(index) > items->GetLength()) {
            throw IndexOutOfRange("ListSequence: insert index out of range");
        }
        items->InsertAt(item, static_cast<size_t>(index));
    }
    
    Sequence<T>* Concat(const Sequence<T>& other) const override {
        ListSequence<T>* result = new ListSequence<T>(*this);
        
        for (int i = 0; i < other.GetLength(); ++i) {
            result->Append(other.Get(i));
        }
        
        return result;
    }
    
    LinkedList<T>& GetInternalList() {
        return *items;
    }
    void Clear() {
        delete items;
        items = new LinkedList<T>();
    }
    void RemoveAt(int index) {
        if (index < 0 || static_cast<size_t>(index) >= items->GetLength()) {
            throw IndexOutOfRange("ListSequence: index out of range");
        }
        LinkedList<T> newList;
        for (size_t i = 0; i < items->GetLength(); ++i) {
            if (static_cast<int>(i) != index) {
                newList.Append(items->Get(i));
            }
        }
        delete items;
        items = new LinkedList<T>(newList);
    }
};