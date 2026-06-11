#include "LinkedList.hpp"

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template<typename T>
LinkedList<T>::LinkedList(const T* items, size_t count) : LinkedList() {
    for (size_t i = 0; i < count; ++i) Append(items[i]);
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : LinkedList() {
    Node* cur = other.head;
    while (cur) {
        Append(cur->data);
        cur = cur->next;
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
        Node* cur = other.head;
        while (cur) {
            Append(cur->data);
            cur = cur->next;
        }
    }
    return *this;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(size_t index) const {
    if (index >= length) throw IndexOutOfRange("LinkedList::getNode: index out of range");

    Node* cur;
    if (index < length / 2) {
        cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
    } else {
        cur = tail;
        for (size_t i = length - 1; i > index; --i) cur = cur->prev;
    }
    return cur;
}

template<typename T>
T& LinkedList<T>::GetFirst() {
    if (!length) throw EmptyContainerError("LinkedList::GetFirst: list is empty");
    return head->data;
}

template<typename T>
const T& LinkedList<T>::GetFirst() const {
    if (!length) throw EmptyContainerError("LinkedList::GetFirst: list is empty");
    return head->data;
}

template<typename T>
T& LinkedList<T>::GetLast() {
    if (!length) throw EmptyContainerError("LinkedList::GetLast: list is empty");
    return tail->data;
}

template<typename T>
const T& LinkedList<T>::GetLast() const {
    if (!length) throw EmptyContainerError("LinkedList::GetLast: list is empty");
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
    Node* n = new Node(item, tail, nullptr);
    if (tail) tail->next = n;
    else head = n;
    tail = n;
    ++length;
}

template<typename T>
void LinkedList<T>::Prepend(const T& item) {
    Node* n = new Node(item, nullptr, head);
    if (head) head->prev = n;
    else tail = n;
    head = n;
    ++length;
}

template<typename T>
void LinkedList<T>::InsertAt(const T& item, size_t index) {
    if (index > length) throw IndexOutOfRange("LinkedList::InsertAt: index out of range");

    if (index == 0) {
        Prepend(item);
        return;
    }
    if (index == length) {
        Append(item);
        return;
    }

    Node* cur = getNode(index);
    Node* n = new Node(item, cur->prev, cur);
    cur->prev->next = n;
    cur->prev = n;
    ++length;
}

template<typename T>
LinkedList<T> LinkedList<T>::GetSubList(size_t startIndex, size_t endIndex) const {
    if (startIndex > endIndex || endIndex >= length)
        throw IndexOutOfRange("LinkedList::GetSubList: invalid indices");

    LinkedList<T> r;
    Node* cur = getNode(startIndex);
    for (size_t i = startIndex; i <= endIndex; ++i) {
        r.Append(cur->data);
        cur = cur->next;
    }
    return r;
}

template<typename T>
LinkedList<T> LinkedList<T>::Concat(const LinkedList& other) const {
    LinkedList<T> r(*this);
    Node* cur = other.head;
    while (cur) {
        r.Append(cur->data);
        cur = cur->next;
    }
    return r;
}

template<typename T>
void LinkedList<T>::Clear() {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
    length = 0;
}

template class LinkedList<int>;
template class LinkedList<double>;
