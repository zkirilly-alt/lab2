#pragma once
#include "Sequence.hpp"
#include "DynamicArray.hpp"

template<typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> items;

    void checkIndex(int index) const {
        if (index < 0 || static_cast<size_t>(index) >= items.GetSize()) {
            throw IndexOutOfRange(index, items.GetSize());
        }
    }

public:
    ArraySequence() : items() {}
    ArraySequence(const T* data, int count) : items(data, static_cast<size_t>(count)) {}
    ArraySequence(const DynamicArray<T>& array) : items(array) {}
    ArraySequence(const ArraySequence<T>& other) : items(other.items) {}
    ArraySequence(ArraySequence&& other) noexcept : items(std::move(other.items)) {}

    ArraySequence<T>& operator=(const ArraySequence<T>& other) {
        if (this != &other) items = other.items;
        return *this;
    }

    ArraySequence<T>& operator=(ArraySequence&& other) noexcept {
        if (this != &other) {
            items = std::move(other.items);
        }
        return *this;
    }

    ~ArraySequence() {}

    T GetFirst() const override {
        if (items.GetSize() == 0) throw EmptyContainerError("ArraySequence::GetFirst: последовательность пуста");
        return items.Get(0);
    }

    T GetLast() const override {
        if (items.GetSize() == 0) throw EmptyContainerError("ArraySequence::GetLast: последовательность пуста");
        return items.Get(items.GetSize() - 1);
    }

    T Get(int index) const override {
        checkIndex(index);
        return items.Get(static_cast<size_t>(index));
    }

    void Set(int index, const T& value) {
        if (index < 0 || static_cast<size_t>(index) >= items.GetSize()) {
            throw IndexOutOfRange(index, items.GetSize());
        }
        items.Set(static_cast<size_t>(index), value);
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        checkIndex(startIndex);
        checkIndex(endIndex);
        if (startIndex > endIndex) throw InvalidArgumentError("ArraySequence::GetSubsequence: начальный индекс больше конечного");
        int newSize = endIndex - startIndex + 1;
        ArraySequence<T>* result = new ArraySequence<T>();
        for (int i = 0; i < newSize; ++i) {
            result->Append(items.Get(static_cast<size_t>(startIndex + i)));
        }
        return result;
    }

    int GetLength() const override { return static_cast<int>(items.GetSize()); }

    void Append(const T& item) override { items.Append(item); }

    void Prepend(const T& item) override {
        int newSize = static_cast<int>(items.GetSize()) + 1;
        T* tempData = new T[static_cast<size_t>(newSize)];
        tempData[0] = item;
        for (int i = 0; i < static_cast<int>(items.GetSize()); ++i) {
            tempData[i + 1] = items.Get(static_cast<size_t>(i));
        }
        items = DynamicArray<T>(tempData, static_cast<size_t>(newSize));
        delete[] tempData;
    }

    void InsertAt(const T& item, int index) override {
        if (index < 0 || static_cast<size_t>(index) > items.GetSize()) {
            throw IndexOutOfRange(index, items.GetSize() + 1);
        }
        int newSize = static_cast<int>(items.GetSize()) + 1;
        T* tempData = new T[static_cast<size_t>(newSize)];
        for (int i = 0; i < index; ++i) tempData[i] = items.Get(static_cast<size_t>(i));
        tempData[index] = item;
        for (int i = index; i < static_cast<int>(items.GetSize()); ++i) {
            tempData[i + 1] = items.Get(static_cast<size_t>(i));
        }
        items = DynamicArray<T>(tempData, static_cast<size_t>(newSize));
        delete[] tempData;
    }

    Sequence<T>* Concat(const Sequence<T>& other) const override {
        ArraySequence<T>* result = new ArraySequence<T>(*this);
        for (int i = 0; i < other.GetLength(); ++i) result->Append(other.Get(i));
        return result;
    }

    void RemoveAt(int index) override {
        if (index < 0 || static_cast<size_t>(index) >= items.GetSize()) {
            throw IndexOutOfRange(index, items.GetSize());
        }
        size_t newSize = items.GetSize() - 1;
        T* tempData = new T[newSize];
        for (size_t i = 0; i < static_cast<size_t>(index); ++i) tempData[i] = items.Get(i);
        for (size_t i = static_cast<size_t>(index) + 1; i < items.GetSize(); ++i) {
            tempData[i - 1] = items.Get(i);
        }
        items = DynamicArray<T>(tempData, newSize);
        delete[] tempData;
    }

    void Clear() override { items = DynamicArray<T>(); }

    DynamicArray<T>& GetInternalArray() { return items; }
    const DynamicArray<T>& GetInternalArray() const { return items; }

    using Iterator = typename DynamicArray<T>::Iterator;
    using ConstIterator = typename DynamicArray<T>::ConstIterator;
    Iterator begin() { return items.begin(); }
    Iterator end() { return items.end(); }
    ConstIterator begin() const { return items.begin(); }
    ConstIterator end() const { return items.end(); }
};