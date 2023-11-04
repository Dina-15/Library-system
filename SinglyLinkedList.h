#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#include <string>
#include "IList.h"

template <typename T>
class SinglyLinkedList : public IList<T>
{
private:

public:
    SinglyLinkedList();
    ~SinglyLinkedList();
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
#endif // SINGLYLINKEDLIST_H

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
{
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    while (this->head != NULL)
    {
        Node<T> *temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    this->tail=NULL;
    this->size = 0;
}
template <typename T>
int SinglyLinkedList<T>::getSize(){return this->size;}
template <typename T>
Node<T>* SinglyLinkedList<T>::begin(){return this->head;}
template <typename T>
Node<T>* SinglyLinkedList<T>::end(){return this->tail;}
template <typename T>
void SinglyLinkedList<T>::push_back(const T value)
{
    Node<T> *newNode = new Node<T>(value);
    if (this->size == 0)
    {
        this->head =this->tail = newNode;
        newNode->next=NULL;
    }
    else
    {
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->size++;
    this->itr.end(this->tail);
}
template <typename T>
void SinglyLinkedList<T>::push_front(const T value)
{
    Node<T> *newNode = new Node<T>(value);
    if(this->size==0)
    {
        this->head =this->tail = newNode;
        newNode->next=NULL;
    } 
    else{
    newNode->next = this->head;
    this->head = newNode;
    this->itr.begin(this->head);
    }
    this->size++;
}
template <typename T>
void SinglyLinkedList<T>::push_at(int index, const T value)
{
    if (index == 0)
    {
        push_front(value);
    }
    else if(index==this->size)
    {
        push_back(value);
    }
    else
    {
        Node<T> *newNode = new Node<T>(value);
        this->itr.begin(this->head);
        for (int i=1 ;i < index ; ++i) ++this->itr;// move the iterator to the node before pos.
        newNode->next = this->itr.current->next;
        this->itr.current->next = newNode;
        ++this->itr;
        this->size++;
    }
}
template <typename T>
T SinglyLinkedList<T>::pop_back()
{
    T value;
    if(this->head->next==nullptr)
    {
        value= this->head->data;
        delete this->head;
        this->head=this->tail=nullptr;
    }
    else
    {
        this->itr.begin(this->head);
        while( this->itr.current->next->next) ++this->itr; // move the iterator to the second-to-last node
        value = this->itr.current->next->data;
        delete this->itr.current->next;
        this->tail = this->itr.current;
        this->itr.current->next = NULL;
    }
    this->size--;
    return value;
}
template <typename T>
T SinglyLinkedList<T>::pop_front()
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
    delete this->itr.current;
    this->itr.begin(this->head);
    }
    this->size--;
    return value;
}
template <typename T>
T SinglyLinkedList<T>::remove_at(int index)
{
    if (index == 0)
        return pop_front();
    else if (index == this->size-1 )
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
        delete temp;
        this->size--;
        return value;
    }
}
template <typename T>
T SinglyLinkedList<T>::retreive(int index)
{
    if(index==0)
        return this->head->data;
    else if(index==this->size-1)
        return this->tail->data;
    else
    {
        this->itr.begin(this->head);
        for(int i=0 ; i < index ; ++i)// move the iterator to the node of the pos.
            ++this->itr;
        return this->itr.current->data;
    }
}
template <typename T>
T SinglyLinkedList<T>:: Edit(std::string key, bool (*pf)(T, std::string), T new_value)
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
T SinglyLinkedList<T>::find(std::string key, bool (*pf)(T, std::string))
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
Node<T>* SinglyLinkedList<T>::partition(Node<T>* start, Node<T> *end, bool(*pf)(T, T))
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
void SinglyLinkedList<T>::sort(Node<T> *start, Node<T> *end, bool(*pf)(T, T))
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
void SinglyLinkedList<T>::reverse()
{
    if(this->head==NULL)
    return;
    Node<T>* prev=NULL;
    Node<T>* next=NULL;
    this->itr.begin(this->head);
    while(this->itr.current!=NULL)
    {
        next=this->itr.current->next;
        this->itr.current->next = prev;
        prev = this->itr.current;
        this->itr.current=next;
    }
    this->tail = this->head;
    this->head=prev;
    
}
