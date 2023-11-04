#ifndef ILIST_H
#define ILIST_H
#include <string.h>
#include "Node.h"
#include "Iterator.h"
template <typename T>
class IList
{
private:

protected:
    Node<T>* head;
    Node<T>* tail;
    Iterator<T> itr;
    int size;
public:
    IList();
    ~IList();
    virtual int getSize()=0;
    virtual void push_back(const T value)=0;
    virtual void push_front(const T value)=0;
    virtual void push_at(int index,const T value)=0;
    virtual T pop_back()=0;
    virtual T pop_front()=0;
    virtual T remove_at(int index)=0;
    virtual T retreive(int index)=0;
    virtual T Edit(std::string key, bool (*pf)(T, std::string), T new_value)=0;
    virtual T find(std::string key, bool(*pf)(T, std::string))=0; // linear search
    virtual Node<T>* partition(Node<T>* start, Node<T> *end, bool(*pf)(T, T))=0;
    virtual void sort(Node<T> *start, Node<T> *end, bool(*pf)(T, T))=0; // quick sort
    virtual void reverse()=0;
    class notFound{};
    virtual Node<T>* begin()=0;
    virtual Node<T>* end()=0;
};
template <typename T>
IList<T>::IList()
{
}
template <typename T>
IList<T>::~IList()
{
}
#endif // ILIST_H
