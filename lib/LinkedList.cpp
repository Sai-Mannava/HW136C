#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "LinkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList() : _size(0), _head(nullptr), _tail(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&other) : _size(other._size),
                                                   _head(other._head),
                                                   _tail(other._tail)
{
    other._size = 0;
    other._head = nullptr;
    other._tail = nullptr;
}

template <typename T>
size_t LinkedList<T>::size() const { return _size; }

template <typename T>
LinkedListNode<T> *LinkedList<T>::head() const { return _head; }

template <typename T>
LinkedListNode<T> *LinkedList<T>::tail() const { return _tail; }

template <typename T>
LinkedListNode<T> *LinkedList<T>::find(T value) const
{
    LinkedListNode<T> *node = _head;
    while (node != nullptr && node->value != value) {
        node = node->next();
    }
    return node;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::prepend(T value)
{
    LinkedListNode<T> *newNode = new LinkedListNode<T>(value, _head);
    _head = newNode;
    if (_tail == nullptr) {
        _tail = newNode;
    }
    _size++;
    return newNode;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::append(T value)
{
    LinkedListNode<T> *newNode = new LinkedListNode<T>(value);
    if (_tail == nullptr) {
        _head = newNode;
        _tail = newNode;
    } else {
        _tail->next() = newNode;
        _tail = newNode;
    }
    _size++;
    return newNode;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::insertAfter(LinkedListNode<T> *node, T value)
{
    LinkedListNode<T> *newNode = new LinkedListNode<T>(value, node->next());
    node->next() = newNode;
    if (_tail == node) {
        _tail = newNode;
    }
    _size++;
    return newNode;
}

template <typename T>
std::optional<T> LinkedList<T>::removeHead()
{
    if (_head == nullptr) {
        return std::nullopt;
    }

    LinkedListNode<T> *node = _head;
    _head = _head->next();
    if (_head == nullptr) {
        _tail = nullptr;
    }
    _size--;

    T value = node->value;
    delete node;
    return value;
}

template <typename T>
bool LinkedList<T>::remove(T value)
{
    LinkedListNode<T> *prev = nullptr;
    LinkedListNode<T> *node = _head;
    while (node != nullptr && node->value != value) {
        prev = node;
        node = node->next();
    }

    if (node == nullptr) {
        return false;
    }

    if (prev == nullptr) {
        _head = node->next();
    } else {
        prev->next() = node->next();
    }
    if (node == _tail) {
        _tail = prev;
    }
    _size--;

    delete node;
    return true;
}

template <typename T>
void LinkedList<T>::clear()
{
    while (_head != nullptr) {
        LinkedListNode<T> *node = _head;
        _head = _head->next();
        delete node;
    }
    _size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

#endif
