#ifndef ITERATOR_H
#define ITERATOR_H
#include "Node.h"

template <typename T>
class Iterator
{
public:
    Iterator();
    virtual ~Iterator();
    Iterator<T>& operator++();
    void begin(Node<T>* head);
    void end(Node<T>* tail);
    // Iterator<T>& operator=(const Iterator<T>& other);
    // bool operator==(const Iterator<T>& it);
    Node<T>* current;
private:
};

template <typename T>
Iterator<T>::Iterator(){}
template <typename T>
Iterator<T>::~Iterator(){}
template <typename T>
void Iterator<T>::begin(Node<T>* head)
{
    current = head;
}
template <typename T>
void Iterator<T>::end(Node<T>* tail)
{
    current = tail;
}
template <typename T>
Iterator<T>& Iterator<T>::operator++()
{
    current=current->next;
    return *this;
}

/*template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& other)
{
    current=other.current;
    return *this;
}
template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& it)
{
    return current == it.current ;
}*/

#endif // ITERATOR_H

