#ifndef CONTAINER_H
#define CONTAINER_H

template <typename T,typename I, typename L>
class Container
{
private:
    I *list;
    int available, borrowed;
public:
    Container();
    ~Container();
    int containerEmpty();
    int containerfull();
    int containersize();
    int availableItems();
    int borrowedItems();
    void pushFront(T data);
    void pushBack(T data);
    void insertAt(int pos, T data);
    T popFront();
    T popBack();
    T removeAt(int pos);
    T Update(std::string key, bool (*pf)(T, std::string), T new_value);
    T retrieveFront();
    T retrieveBack();
    T retrieveAt(int pos);
    T search(std::string key, bool(*pf)(T, std::string));
    void sort( bool(*pf)(T, T));
    void reverse();
    T borrow(std::string key, bool(*pf)(T, std::string), bool(*pf2)(T));
    class notFound{};
    class notAvailable{};
};
#endif // Container

template <typename T,typename I, typename L>
Container<T,I , L>::Container()
{
    list = new L();
    borrowed=0;
    available=0;
}
template <typename T,typename I, typename L>
Container<T,I, L>::~Container()
{
    delete list;
    available=0;
}
template <typename T,typename I, typename L>
int Container<T,I, L>::availableItems()
{
    return available;
}
template <typename T,typename I, typename L>
int Container<T,I, L>::borrowedItems()
{
    return borrowed;
}
template <typename T,typename I, typename L>
int Container<T,I, L>::containerEmpty()
{
    return list->getSize() == 0;
}
template <typename T,typename I, typename L>
int Container<T,I, L>::containerfull()
{
    return 0;
}
template <typename T,typename I, typename L>
int Container<T,I, L>::containersize()
{
    return list->getSize();
}
template <typename T,typename I, typename L>
void Container<T,I, L>::pushFront(T data)
{
    list->push_front(data);
    available++;
}
template <typename T,typename I, typename L>
void Container<T,I, L>::pushBack(T data)
{
    list->push_back(data);
    available++;
}
template <typename T,typename I,typename L>
void Container<T,I, L>::insertAt(int pos, T data)
{
    list->push_at(pos,data);
    available++;
}
template <typename T,typename I, typename L>
T Container<T,I, L>::popFront()
{
    available--;
    return list->pop_front();
}
template <typename T,typename I, typename L>
T Container<T,I, L>::popBack()
{
    available--;
    return list->pop_back();
}
template <typename T,typename I, typename L>
T Container<T,I, L>::removeAt(int pos)
{
    available--;
    return list->remove_at(pos);
}
template <typename T,typename I, typename L>
T Container<T,I, L>::retrieveFront()
{
    return list->retreive(0);
}
template <typename T,typename I, typename L>
T Container<T,I, L>::retrieveBack()
{
    return list->retreive(list->getSize()-1);
}
template <typename T,typename I, typename L>
T Container<T,I, L>::retrieveAt(int pos)
{
    return list->retreive(pos);
}
template <typename T,typename I, typename L>
T Container<T,I, L>::Update(std::string key, bool (*pf)(T, std::string), T new_value)
{
    try
    {
        return list->Edit(key, *pf, new_value);
    }
    catch (...)
    {
        throw notFound();
    }
}
template <typename T,typename I, typename L>
T Container<T,I, L>::search(std::string key, bool(*pf)(T, std::string))
{
    try{
    return list->find(key,*pf);
    }
    catch(...)
    {
        throw notFound();
    }
}
template <typename T,typename I, typename L>
void Container<T,I, L>::sort(bool(*pf)(T, T))   // QUICK SORT ALGORITHM
{
    list->sort(list->begin(), list->end(), *pf);
}
template <typename T,typename I, typename L>
void Container<T,I, L>::reverse()
{
    list->reverse();
}
template <typename T,typename I, typename L>
T Container<T,I, L>::borrow(std::string key, bool(*pf)(T, std::string), bool(*pf2)(T))
{
    try
    {
        T element = list->find(key, *pf);
        if( ! (*pf2)(element))
        {
            throw notAvailable();
        }
        available--;
        borrowed++;
        return element;
    }
    catch (const notAvailable)
    {
        throw notAvailable();
    }
    catch (...)
    {
        throw notFound();
    }
}