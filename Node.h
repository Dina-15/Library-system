#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
    Node(T data);
    virtual ~Node();
    bool operator==(const Node<T>& n);
    bool operator==(const long long int num);
    Node<T>* next;
    Node<T>* prev;
    T data;
private:
};
template <typename T>
Node<T>::Node(T data)
{
    this->data=data;
    this->next=NULL;
    this->prev=NULL;
}
template <typename T>
Node<T>::~Node(){}

template <typename T>
bool Node<T>::operator==(const Node<T>& n)
{
    return next == n.next ;
}
template <typename T>
bool Node<T>::operator==(const long long int num)
{
    return next == NULL ;
}

#endif // NODE_H
