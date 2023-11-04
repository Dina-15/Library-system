#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <string>
#include "IList.h"

template<typename T>
class DoublyLinkedList : public IList<T>
{
private:

public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    int getSize();
    void push_back(const T value);
    void push_front(const T value);
    void push_at(int index, const T value);
    T pop_back();
    T pop_front();
    T remove_at(int index);
    T retreive(int index);
    T Edit(std::string key, bool (*pf)(T, std::string), T new_value);
    Node<T>* partition(Node<T>* start, Node<T> *end, bool(*pf)(T, T));
    void sort(Node<T> *start, Node<T> *end, bool(*pf)(T, T));
    T find(std::string key, bool (*pf)(T, std::string));
    void reverse();
    class notFound{};
    Node<T>* begin();
    Node<T>* end();
};
#endif
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    this->head=nullptr;
    this->tail=nullptr;
    this->size = 0;
}
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    Node<T> *temp;
    while (this->head != nullptr)
    {
        temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    this->tail=nullptr;
    this->size = 0;
}
template <typename T>
int DoublyLinkedList<T>::getSize(){return this->size;}
template <typename T>
Node<T>* DoublyLinkedList<T>::begin(){return this->head;}
template <typename T>
Node<T>* DoublyLinkedList<T>::end(){return this->tail;}
template <typename T>
void DoublyLinkedList<T>::push_back(const T value)
{
    Node<T> *newNode = new Node<T>(value);
    if (this->size == 0)
    {
        this->head =this->tail = newNode;
        newNode->next=newNode->prev=nullptr;
    }
    else
    {
        newNode->next=nullptr;
        newNode->prev=this->tail;
        this->tail->next = newNode;
        this->tail=newNode;
    }
    this->itr.end(this->tail);
    this->size++;    
}
template <typename T>
void DoublyLinkedList<T>::push_front(const T value)
{
    Node<T> *newNode = new Node<T>(value);
    if(this->size==0)
    {
        this->head =this->tail = newNode;
        newNode->next=newNode->prev=nullptr;
    } 
    else{
    newNode->next = this->head;
    newNode->prev=nullptr;
    this->head->prev=newNode;
    this->head = newNode;
    }
    this->itr.begin(this->head);
    this->size++;
}
template <typename T>
void DoublyLinkedList<T>::push_at(int index, const T value)
{
    if (index == 0)
    {
        push_front(value);
    }
    else if (index == this->size)
    {
        push_back(value);
    }
    else
    {
        Node<T> *newNode = new Node<T>(value);
        this->itr.begin(this->head);
        for (int i=1 ;i < index; ++i) ++this->itr;// move the iterator to the node of pos.
        newNode->next=this->itr.current->next;
        newNode->prev=this->itr.current;
        this->itr.current->next=newNode;
        this->itr.current->next->prev=newNode;
        this->size++;
    }
}
template <typename T>
T DoublyLinkedList<T>::pop_back()
{
    T value;
    if(this->size==1)
    {
        value= this->head->data;
        delete this->head;
        this->head=this->tail=nullptr;
    }
    else
    {
        this->itr.end(this->tail);
        this->tail=this->tail->prev;
        this->tail->next=nullptr;
        delete this->itr.current;
    }
    this->size--;
    return value;
}
template <typename T>
T DoublyLinkedList<T>::pop_front()
{
    T value;
    if(this->size==1)
    {
        value= this->head->data;
        delete this->head;
        this->head=this->tail=nullptr;
    }
    else{
    this->itr.begin(this->head);
    value = this->itr.current->data;
    this->head = this->head->next;
    this->head->prev=nullptr;
    delete this->itr.current;
    }
    this->itr.begin(this->head);
    this->size--;
    return value;
}
template <typename T>
T DoublyLinkedList<T>::remove_at(int index)
{
    if(index==0)
    {
        return pop_front();
    }
    else if (index == this->size - 1)
    {
        return pop_back();
    }
    else
    {
        this->itr.begin(this->head);
        for(int i=1; i< index ;i++) ++this->itr;
        // move the iterator to the node before the pos.
        T value = this->itr.current->next->data;
        Node<T> *temp = this->itr.current->next;
        this->itr.current->next = temp->next;
        temp->next->prev=this->itr.current;
        delete temp;
        this->size--;
        return value;
    }
}
template <typename T>
T DoublyLinkedList<T>::retreive(int index)
{
    if(index==0)
        return this->head->data;
    else if(index==this->size-1)
        return this->tail->data;
    else
    {
        this->itr.begin(this->head);
        for(int i=0; i < index ; ++i)// move the iterator to the node of the pos.
            ++this->itr;
        return this->itr.current->data;
    }
}
template <typename T>
T DoublyLinkedList<T>:: Edit(std::string key, bool (*pf)(T, std::string), T new_value)
{
    for(int i=0; i<this->size;i++)
    {
        if ((*pf)(this->itr.current->data, key))
        {
            this->itr.current->data = new_value;
            break;
        }
        ++this->itr;
    }
    return this->itr.current->data;
    throw notFound();
}
template <typename T>
T DoublyLinkedList<T>::find(std::string key, bool (*pf)(T, std::string))
{
    this->itr.begin(this->head);
    for(int i=0; i<this->size;i++)
    {
        if ((*pf)(this->itr.current->data, key))
            return this->itr.current->data;
        ++this->itr;
    }
    throw notFound();
}
template <typename T>
Node<T>* DoublyLinkedList<T>::partition(Node<T>* start, Node<T> *end, bool(*pf)(T, T))
{
    if(start==end || start==NULL || end==NULL)
        return start;
    Node<T> *pivot_prev = start;
    Node<T> *current=start;
    T pivot = end->data;
    while(!(start == end))
    {   if((*pf)(start->data, pivot))
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
void DoublyLinkedList<T>::sort(Node<T> *start, Node<T> *end, bool(*pf)(T, T))
{
    if(start==end)
        return;
    Node<T>* pivot_prev = partition(start, end, *pf);
    sort(start, pivot_prev, *pf);
    if(!(pivot_prev == NULL) && pivot_prev == start)
        sort(pivot_prev->next, end, *pf);
    else if(!(pivot_prev == NULL) && !(pivot_prev->next == NULL))
        sort(pivot_prev->next->next, end, *pf);
}
template <typename T>
void DoublyLinkedList<T>::reverse()
{
    this->itr.begin(this->head);
    Node<T>* h=this->head;
    Node<T>* temp = this->head->next;
    this->head->next = NULL;
    this->head->prev= temp;
    while(temp != NULL)
    {
        temp->prev = temp->next;
        temp->next = this->itr.current;
        this->itr.current = temp;
        temp = temp->prev;
    }
    this->head = this->itr.current;
    this->tail = h;
}
