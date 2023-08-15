#ifndef ITERATOR_H
#define ITERATOR_H

template <typename U>
class Iterator
{
public:
    Iterator();
    virtual ~Iterator();
    Iterator<U> operator++();
    bool operator==(const Iterator<U>& it);
    template <typename T>
    friend class Container;
private:
    Node<U>* current;
    int pos;
};

template <typename U>
Iterator<U>::Iterator()
{
    current=NULL;
    pos=0;
}
template <typename U>
Iterator<U>::~Iterator()
{

}
template <typename U>
bool Iterator<U>::operator==(const Iterator<U>& it)
{
    return current == it.current ;
}
template <typename U>
Iterator<U> Iterator<U>::operator++()
{
    this->current=current->next;
    this->pos++;
    return *this;
}

#endif // ITERATOR_H

