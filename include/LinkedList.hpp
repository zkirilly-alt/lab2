#pragma once
#include "Exception.hpp"
#include <cstddef>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& data, Node* prev = nullptr, Node* next = nullptr);
    };

    Node* head;
    Node* tail;
    size_t length;

    Node* getNode(size_t index) const;

public:
    LinkedList();
    LinkedList(const T* items, size_t count);
    LinkedList(const LinkedList& other);
    ~LinkedList();
    LinkedList& operator=(const LinkedList& other);

    T& GetFirst();
    const T& GetFirst() const;
    T& GetLast();
    const T& GetLast() const;
    T& Get(size_t index);
    const T& Get(size_t index) const;
    size_t GetLength() const;

    void Append(const T& item);
    void Prepend(const T& item);
    void InsertAt(const T& item, size_t index);
    LinkedList GetSubList(size_t startIndex, size_t endIndex) const;
    LinkedList Concat(const LinkedList& other) const;
    void Clear();

    class Iterator;
    class ConstIterator;
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
};



template<typename T>
class LinkedList<T>::Iterator {
private:
    Node* current;
public:
    Iterator(Node* node) : current(node) {}
    T& operator*() { return current->data; }
    Iterator& operator++() { current = current->next; return *this; }
    Iterator operator++(int) { Iterator tmp = *this; current = current->next; return tmp; }
    bool operator==(const Iterator& other) const { return current == other.current; }
    bool operator!=(const Iterator& other) const { return current != other.current; }
};

template<typename T>
class LinkedList<T>::ConstIterator {
private:
    const Node* current;
public:
    ConstIterator(const Node* node) : current(node) {}
    const T& operator*() const { return current->data; }
    ConstIterator& operator++() { current = current->next; return *this; }
    ConstIterator operator++(int) { ConstIterator tmp = *this; current = current->next; return tmp; }
    bool operator==(const ConstIterator& other) const { return current == other.current; }
    bool operator!=(const ConstIterator& other) const { return current != other.current; }
};