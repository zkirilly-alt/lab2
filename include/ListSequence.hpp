#pragma once
#include "Sequence.hpp"
#include "LinkedList.hpp"

template<typename T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> items;

    void checkIndex(int index) const {
        if (index < 0 || static_cast<size_t>(index) >= items.GetLength()) {
            throw IndexOutOfRange(static_cast<size_t>(index), items.GetLength());
        }
    }

public:
    ListSequence() : items() {}
    ListSequence(const T* data, int count) : items(data, static_cast<size_t>(count)) {}
    ListSequence(const LinkedList<T>& list) : items(list) {}
    ListSequence(const ListSequence<T>& other) : items(other.items) {}
    ListSequence(ListSequence&& other) noexcept : items(std::move(other.items)) {}

    ListSequence<T>& operator=(const ListSequence<T>& other) {
        if (this != &other) items = other.items;
        return *this;
    }

    ListSequence<T>& operator=(ListSequence&& other) noexcept {
        if (this != &other) {
            items = std::move(other.items);
        }
        return *this;
    }

    ~ListSequence() {}

    T GetFirst() const override {
        if (items.GetLength() == 0) throw EmptyContainerError("ListSequence::GetFirst: последовательность пуста");
        return items.GetFirst();
    }

    T GetLast() const override {
        if (items.GetLength() == 0) throw EmptyContainerError("ListSequence::GetLast: последовательность пуста");
        return items.GetLast();
    }

    T Get(int index) const override {
        checkIndex(index);
        return items.Get(static_cast<size_t>(index));
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        checkIndex(startIndex);
        checkIndex(endIndex);
        if (startIndex > endIndex) throw InvalidArgumentError("ListSequence::GetSubsequence: начальный индекс больше конечного");
        LinkedList<T> sublist = items.GetSubList(static_cast<size_t>(startIndex), static_cast<size_t>(endIndex));
        return new ListSequence<T>(sublist);
    }

    int GetLength() const override { return static_cast<int>(items.GetLength()); }

    void Append(const T& item) override { items.Append(item); }
    void Prepend(const T& item) override { items.Prepend(item); }

    void InsertAt(const T& item, int index) override {
        if (index < 0 || static_cast<size_t>(index) > items.GetLength()) {
            throw IndexOutOfRange(static_cast<size_t>(index), items.GetLength());
        }
        items.InsertAt(item, static_cast<size_t>(index));
    }

    Sequence<T>* Concat(const Sequence<T>& other) const override {
        ListSequence<T>* result = new ListSequence<T>(*this);
        for (int i = 0; i < other.GetLength(); ++i) result->Append(other.Get(i));
        return result;
    }

    void RemoveAt(int index) override {
        if (index < 0 || static_cast<size_t>(index) >= items.GetLength()) {
            throw IndexOutOfRange(static_cast<size_t>(index), items.GetLength());
        }
        LinkedList<T> newList;
        for (size_t i = 0; i < items.GetLength(); ++i) {
            if (static_cast<int>(i) != index) newList.Append(items.Get(i));
        }
        items = newList;
    }

    void Clear() override { items = LinkedList<T>(); }

    LinkedList<T>& GetInternalList() { return items; }
    const LinkedList<T>& GetInternalList() const { return items; }

    using Iterator = typename LinkedList<T>::Iterator;
    using ConstIterator = typename LinkedList<T>::ConstIterator;
    Iterator begin() { return items.begin(); }
    Iterator end() { return items.end(); }
    ConstIterator begin() const { return items.begin(); }
    ConstIterator end() const { return items.end(); }
};