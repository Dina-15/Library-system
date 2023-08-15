#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <string.h>
#include "Node.h"
#include "Iterator.h"

using namespace std;
template <typename T>
class Container
{
public:
    Container();
    virtual ~Container();

    Node<T>* begin();
    Node<T>* end();
    Node<T>* prev();
    Node<T>* next();
    int containerEmpty();
    int containerfull();
    int containersize();
    int availableBooks();
    int borrowedBooks();
    void insertFront(T data);
    void insertBack(T data);
    void insertAt(T data,int pos);
    void remove();
    void removeAt(int pos);
    T find(string key);
    T borrow(string key);
    T retrieve(int pos);
    Node<T>* partition(Node<T> *start, Node<T> *end);
    void sort(Node<T> *start, Node<T> *end);

    class notFound{};
private:
    Node<T>* head;
    Iterator<T> itr;
    int size, available, borrowed;
};

template <typename T>
Container<T>::Container()
{
    head = NULL;
    size =0;
    borrowed=0;
    available=0;
}
template <typename T>
Container<T>::~Container()
{
    this->remove();
}

template <typename T>
int Container<T>::containerEmpty()
{
    return size==0;
}
template <typename T>
int Container<T>::containerfull()
{
    return 0;
}
template <typename T>
int Container<T>::containersize()
{
    return size;
}
template <typename T>
int Container<T>::availableBooks()
{
    return available;
}
template <typename T>
int Container<T>::borrowedBooks()
{
    return borrowed;
}
template <typename T>
void Container<T>::insertFront(T data)
{
    Node<T>* newNode = new Node<T>(data);
    newNode->next=head;
    head=newNode;
    itr.current=head;
    itr.pos = 0;
    ++size;
    ++available;
}
template <typename T>
void Container<T>::insertBack(T data)
{
    Node<T>* newNode = new Node<T>(data);
    if(size==0)
    {
        newNode->next=head;
        head=newNode;
        itr.current=head;
        itr.pos = 0;
    }
    else
    {
        for(; itr.pos<size-1; ++itr);
        newNode->next=NULL;
        itr.current->next=newNode;
    }
    ++size;
    ++available;
}
template <typename T>
void Container<T>::insertAt(T data,int pos)
{
    Node<T>* newNode = new Node<T>(data);
    if(pos==0)
    {
        newNode->next=head;
        head=newNode;
        itr.current=head;
        itr.pos=0;
    }
    else
    {
        if(pos<=itr.pos)
        {
            itr.current=head;
            itr.pos=0;
        }
        for(; itr.pos<pos-1; ++itr);
        newNode->next=itr.current->next;
        itr.current->next=newNode;
    }
    ++size;
    ++available;
}
template <typename T>
void Container<T>::remove() // clear the container
{
    Node<T> *temp=head;
    while(head)
    {
        temp=head->next;
        delete head;
        head=temp;
    }
    size=0;
    available=0;
}
template <typename T>
void Container<T>::removeAt(int pos)
{
    Node<T>* temp;
    if(pos==0)
    {
        itr.current=head->next;
        delete head;
        head=itr.current;
        itr.current=head;
        itr.pos = 0;
    }
    else
    {
        if(pos<=itr.pos)
        {
            itr.current=head;
            itr.pos=0;
        }
        for(; itr.pos<pos-1; ++itr);
        temp=itr.current->next->next;
        delete itr.current->next;
        itr.current->next=temp;
    }
    --size;
    --available;
}
template <typename T>
T Container<T>::find(string key)
{
    itr.current=head;
    itr.pos=0;
    for(; itr.pos <size; ++itr)
    {
        if(key==itr.current->data.title || key==itr.current->data.author || key==itr.current->data.genre || key==itr.current->data.ISBN)
            return itr.current->data;
    }
    throw notFound();
}
template <typename T>
T Container<T>::borrow(string key)
{
    itr.current=head;
    itr.pos=0;
    for(; itr.pos <size; ++itr)
    {
        if((key==itr.current->data.title || key==itr.current->data.author || key==itr.current->data.genre || key==itr.current->data.ISBN) && itr.current->data.status == "available")
        {
            --available;
            ++borrowed;
            itr.current->data.status = "unavailable";
            return itr.current->data;
        }
    }
    throw notFound();
}
template <typename T>
T Container<T>::retrieve(int pos)
{
    if(pos==0)
        return head->data;
    else
    {
        if(pos>=itr.pos)
        {
            for(int i=itr.pos; i<pos; ++i)
                ++itr;
        }
        else if(pos<=itr.pos)
        {
            itr.current=head;
            itr.pos=0;
            for(int i=0; i<pos; ++i)
                ++itr;
        }
        return itr.current->data;
    }
}
template <typename T>
Node<T>* Container<T>::partition(Node<T>* start, Node<T> *end)
{
    if(start==end || start==NULL || end==NULL)
        return start;
    Node<T> *pivot_prev = start;
    Node<T> *current=start;
    T pivot = end->data;
    while(!(start == end))
    {
        if(start->data.title < pivot.title) // sorting based on title
        {
            pivot_prev=current;
            T temp = current->data;
            current->data=start->data;
            start->data=temp;
            current=current->next;
        }
        start =start->next;
    }
    T temp = current->data;
    current->data=pivot;
    end->data=temp;

    return pivot_prev;
}
template <typename T>
void Container<T>::sort(Node<T> *start, Node<T> *end) // QUICK SORT ALGORITHM
{
    if(start==end)
        return;
    Node<T>* pivot_prev = partition(start, end);
    sort(start, pivot_prev);
    if(!(pivot_prev == NULL) && pivot_prev == start)
        sort(pivot_prev->next, end);
    else if(!(pivot_prev == NULL) && !(pivot_prev->next == NULL))
        sort(pivot_prev->next->next, end);
}
template <typename T>
Node<T>* Container<T>::begin()
{
    return head;
}
template <typename T>
Node<T>* Container<T>::end()
{
    if(size==0)
    {
        return head;
    }
    else
    {
        for(; itr.pos<size-1; ++itr);
        return itr.current;
    }
}
template <typename T>
Node<T>* Container<T>::prev()
{
    int temp=itr.pos;
    itr.current=head;
    itr.pos=0;
    for(int i=0; i<temp; ++i)
        ++itr;
    return itr.current;
}
template <typename T>
Node<T>* Container<T>::next()
{
    return itr.current->next;
}

#endif //Container
