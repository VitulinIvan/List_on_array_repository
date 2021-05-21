#pragma once

#include <iostream>

using namespace std;

template <class T1>
class TArrayList;

template <class T>
class TArrayListIterator
{
    protected:
        TArrayList<T>& list;
        int index;
    public:
        TArrayListIterator(TArrayList<T>& _list, int _index = -2);
        TArrayListIterator(const TArrayListIterator<T>& _v);
        ~TArrayListIterator();
        TArrayListIterator<T>& operator =(TArrayListIterator<T>& _v);
        bool HasNext();
        bool operator ==(const TArrayListIterator<T>& _v);
        bool operator !=(const TArrayListIterator<T>& _v);
        TArrayListIterator<T>& operator++();
        T& operator*(int);
        T& operator*();
        template <class T1>
        friend class TArrayList;
};

template<class T>
inline TArrayListIterator<T>::TArrayListIterator(TArrayList<T>& _list, int _index) :list(_list), index(_index)
{

}

template<class T>
inline TArrayListIterator<T>::TArrayListIterator(const TArrayListIterator<T>& _v) : list(_v.list), index(_v.index)
{

}

template<class T>
inline TArrayListIterator<T>::~TArrayListIterator()
{
    index = -2;
}

template<class T>
inline TArrayListIterator<T>& TArrayListIterator<T>::operator=(TArrayListIterator<T>& _v)
{
    this->list = _v.list;
    this->index = _v.index;
}

template<class T>
inline bool TArrayListIterator<T>::HasNext()
{
    return index >= 0;
}

template<class T>
inline bool TArrayListIterator<T>::operator==(const TArrayListIterator<T>& _v)
{
    return this->index == _v.index;
}

template<class T>
inline bool TArrayListIterator<T>::operator!=(const TArrayListIterator<T>& _v)
{
    return !this->operator==(_v);
}

template<class T>
inline TArrayListIterator<T>& TArrayListIterator<T>::operator++()
{
    if (HasNext())
        index = list.links[index];
    else
        throw - 1;
    return *this;
}

template<class T>
inline T& TArrayListIterator<T>::operator*(int)
{
    if (index < 0)
        throw - 1;
    return list.data[index];
}

template<class T>
inline T& TArrayListIterator<T>::operator*()
{
    if (index < 0)
        throw - 1;
    return list.data[index];
}