#include "LinkedList.h"

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template<typename T>
LinkedList<T>::LinkedList(const T* items, size_t count) : LinkedList() {
    for (size_t i = 0; i < count; ++i) {
        Append(items[i]);
    }
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : LinkedList() {
    Node* current = other.head;
    while (current) {
        Append(current->data);
        current = current->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
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

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(size_t index) const {
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

template<typename T>
T& LinkedList<T>::GetFirst() {
    if (length == 0) {
        throw EmptyContainerError("LinkedList::GetFirst: list is empty");
    }
    return head->data;
}

template<typename T>
const T& LinkedList<T>::GetFirst() const {
    if (length == 0) {
        throw EmptyContainerError("LinkedList::GetFirst: list is empty");
    }
    return head->data;
}

template<typename T>
T& LinkedList<T>::GetLast() {
    if (length == 0) {
        throw EmptyContainerError("LinkedList::GetLast: list is empty");
    }
    return tail->data;
}

template<typename T>
const T& LinkedList<T>::GetLast() const {
    if (length == 0) {
        throw EmptyContainerError("LinkedList::GetLast: list is empty");
    }
    return tail->data;
}

template<typename T>
T& LinkedList<T>::Get(size_t index) {
    return getNode(index)->data;
}

template<typename T>
const T& LinkedList<T>::Get(size_t index) const {
    return getNode(index)->data;
}

template<typename T>
void LinkedList<T>::Append(const T& item) {
    Node* newNode = new Node(item, tail, nullptr);
    if (tail) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
    ++length;
}

template<typename T>
void LinkedList<T>::Prepend(const T& item) {
    Node* newNode = new Node(item, nullptr, head);
    if (head) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
    ++length;
}

template<typename T>
void LinkedList<T>::InsertAt(const T& item, size_t index) {
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

template<typename T>
LinkedList<T> LinkedList<T>::GetSubList(size_t startIndex, size_t endIndex) const {
    if (startIndex > endIndex || endIndex >= length) {
        throw IndexOutOfRange("LinkedList::GetSubList: invalid indices");
    }
    
    LinkedList<T> result;
    Node* current = getNode(startIndex);
    for (size_t i = startIndex; i <= endIndex; ++i) {
        result.Append(current->data);
        current = current->next;
    }
    return result;
}

template<typename T>
LinkedList<T> LinkedList<T>::Concat(const LinkedList& other) const {
    LinkedList<T> result(*this);
    Node* current = other.head;
    while (current) {
        result.Append(current->data);
        current = current->next;
    }
    return result;
}

template<typename T>
void LinkedList<T>::Clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    length = 0;
}

// Явная инстанциация
template class LinkedList<int>;
template class LinkedList<double>;