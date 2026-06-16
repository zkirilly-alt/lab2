#include "LinkedList.hpp"

template<typename T>
LinkedList<T>::Node::Node(const T& data, Node* prev, Node* next)
    : data(data), next(next), prev(prev) {}

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
LinkedList<T>::LinkedList(LinkedList&& other) noexcept
    : head(other.head), tail(other.tail), length(other.length) {
    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
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
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        Clear();
        head = other.head;
        tail = other.tail;
        length = other.length;
        other.head = nullptr;
        other.tail = nullptr;
        other.length = 0;
    }
    return *this;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(size_t index) const {
    if (index >= length) throw IndexOutOfRange(index, length);
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
    if (length == 0) throw EmptyContainerError("LinkedList::GetFirst: список пуст");
    return head->data;
}

template<typename T>
const T& LinkedList<T>::GetFirst() const {
    if (length == 0) throw EmptyContainerError("LinkedList::GetFirst: список пуст");
    return head->data;
}

template<typename T>
T& LinkedList<T>::GetLast() {
    if (length == 0) throw EmptyContainerError("LinkedList::GetLast: список пуст");
    return tail->data;
}

template<typename T>
const T& LinkedList<T>::GetLast() const {
    if (length == 0) throw EmptyContainerError("LinkedList::GetLast: список пуст");
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
size_t LinkedList<T>::GetLength() const {
    return length;
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
    if (index > length) throw IndexOutOfRange(index, length);
    if (index == 0) Prepend(item);
    else if (index == length) Append(item);
    else {
        Node* cur = getNode(index);
        Node* n = new Node(item, cur->prev, cur);
        cur->prev->next = n;
        cur->prev = n;
        ++length;
    }
}

template<typename T>
LinkedList<T> LinkedList<T>::GetSubList(size_t startIndex, size_t endIndex) const {
    if (startIndex > endIndex || endIndex >= length) throw IndexOutOfRange(startIndex, length);
    LinkedList<T> result;
    Node* cur = getNode(startIndex);
    for (size_t i = startIndex; i <= endIndex; ++i) {
        result.Append(cur->data);
        cur = cur->next;
    }
    return result;
}

template<typename T>
LinkedList<T> LinkedList<T>::Concat(const LinkedList& other) const {
    LinkedList<T> result(*this);
    Node* cur = other.head;
    while (cur) {
        result.Append(cur->data);
        cur = cur->next;
    }
    return result;
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

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::begin() const {
    return ConstIterator(head);
}

template<typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::end() const {
    return ConstIterator(nullptr);
}

template class LinkedList<int>;
template class LinkedList<double>;