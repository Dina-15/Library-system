#ifndef NODE_H
#define NODE_H
#include <string.h>
template <typename M>
class Node
{
public:
    Node(M data);
    virtual ~Node();
    bool operator==(const Node<M>& n);
    bool operator==(const std::string s);
    bool operator==(const long long int num);
template <typename T>
friend class Container;
template <typename U>
friend class Iterator;
private:
    Node<M>* next;
    M data;
};
template <typename M>
Node<M>::Node(M data)
{
  this->data=data;
  this->next=NULL;
}
template <typename M>
Node<M>::~Node()
{

}
template <typename M>
bool Node<M>::operator==(const Node<M>& n)
{
    return next == n.next ;
}
template <typename M>
bool Node<M>::operator==(const std::string s)
{
   return data.title==s;
}
template <typename M>
bool Node<M>::operator==(const long long int num)
{
    return next == NULL ;
}

#endif // NODE_H
