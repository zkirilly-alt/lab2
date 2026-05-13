#pragma once
#include "exceptions.hpp"
#include <cstddef>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
            : data(data), next(next), prev(prev) {}
    };
    
    Node* head;
    Node* tail;
    size_t length;
    
    Node* getNode(size_t index) const {
        if (index >= length) {
            throw IndexOutOfRange("LinkedList::getNode: index out of range");
        }
        
        Node* current;
        if (index < length / 2) {
            current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            current = tail;
            for (size_t i = length - 1; i > index; --i) {
                current = current->prev;
            }
        }
        return current;
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    
    LinkedList(const T* items, size_t count) : LinkedList() {
        for (size_t i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }
    
    LinkedList(const LinkedList& other) : LinkedList() {
        Node* current = other.head;
        while (current) {
            Append(current->data);
            current = current->next;
        }
    }
    
    ~LinkedList() {
        Clear();
    }
    
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            Clear();
            Node* current = other.head;
            while (current) {
                Append(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    T& GetFirst() {
        if (length == 0) {
            throw EmptyContainerError("LinkedList::GetFirst: list is empty");
        }
        return head->data;
    }
    
    const T& GetFirst() const {
        if (length == 0) {
            throw EmptyContainerError("LinkedList::GetFirst: list is empty");
        }
        return head->data;
    }
    
    T& GetLast() {
        if (length == 0) {
            throw EmptyContainerError("LinkedList::GetLast: list is empty");
        }
        return tail->data;
    }
    
    const T& GetLast() const {
        if (length == 0) {
            throw EmptyContainerError("LinkedList::GetLast: list is empty");
        }
        return tail->data;
    }
    
    T& Get(size_t index) {
        return getNode(index)->data;
    }
    
    const T& Get(size_t index) const {
        return getNode(index)->data;
    }
    
    size_t GetLength() const { return length; }
    
    void Append(const T& item) {
        Node* newNode = new Node(item, tail, nullptr);
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        ++length;
    }
    
    void Prepend(const T& item) {
        Node* newNode = new Node(item, nullptr, head);
        if (head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        ++length;
    }
    
    void InsertAt(const T& item, size_t index) {
        if (index > length) {
            throw IndexOutOfRange("LinkedList::InsertAt: index out of range");
        }
        
        if (index == 0) {
            Prepend(item);
        } else if (index == length) {
            Append(item);
        } else {
            Node* current = getNode(index);
            Node* newNode = new Node(item, current->prev, current);
            current->prev->next = newNode;
            current->prev = newNode;
            ++length;
        }
    }
    
    LinkedList GetSubList(size_t startIndex, size_t endIndex) const {
        if (startIndex > endIndex || endIndex >= length) {
            throw IndexOutOfRange("LinkedList::GetSubList: invalid indices");
        }
        
        LinkedList result;
        Node* current = getNode(startIndex);
        for (size_t i = startIndex; i <= endIndex; ++i) {
            result.Append(current->data);
            current = current->next;
        }
        return result;
    }
    
    LinkedList Concat(const LinkedList& other) const {
        LinkedList result(*this);
        Node* current = other.head;
        while (current) {
            result.Append(current->data);
            current = current->next;
        }
        return result;
    }
    
    void Clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        length = 0;
    }
};