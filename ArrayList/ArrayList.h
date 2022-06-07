#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "ArrayListIterator.h"

using namespace std;

template <class T1>
class TArrayListIterator;

template <class T>
class TArrayList
{
protected:
    T* data;
    int* links;
    int size;
    int count;
    int root;
public:
    TArrayList(int _size = 1);
    TArrayList(const TArrayList<T>& _v);
    ~TArrayList();
    TArrayList<T>& operator =(const TArrayList<T>& _v);
    void InsFirst(T d);
    void InsLast(T d);
    void Ins(TArrayListIterator<T>& e, T d);
    bool IsEmpty(void) const;
    bool IsFull(void) const;
    TArrayListIterator<T> begin();
    TArrayListIterator<T> end();
    T GetFirst();
    T GetLast();
    int GetCount();
    void DelFirst();
    void DelLast();
    void Del(TArrayListIterator<T>& e);
    template <class T1>
    friend ostream& operator<<(ostream& ostr, const TArrayList<T1>& A);
    template <class T1>
    friend istream& operator>>(istream& istr, TArrayList<T1>& A);
    template <class T1>
    friend ofstream& operator<<(ofstream& ofstr, TArrayList<T1>& A);
    vector<int> ElemsModZero(int k); // Доп. задание 3
    void WriteToFile(string filename); // Доп. задание 2
    template <class T1>
    friend class TArrayListIterator;
};

template<class T>
inline TArrayList<T>::TArrayList(int _size)
{
    if (_size <= 0)
        throw - 1;

    this->size = _size;
    count = 0;
    root = -1;
    data = new T[size];
    links = new int[size];
    for (int i = 0; i < size; i++)
        links[i] = -2;
}

template <class T>
TArrayList<T>::TArrayList(const TArrayList<T>& _v)
{
    this->count = _v.count;
    this->size = _v.size;
    this->root = _v.root;
    data = new T[size];
    links = new int[size];
    for (int i = 0; i < size; i++)
    {
        this->links[i] = _v.links[i];
        this->data[i] = _v.data[i];
    }
}

template <class T>
TArrayList<T>::~TArrayList()
{
    if (data != 0)
    {
        delete[] data;
        delete[] links;
        data = 0;
        links = 0;
        count = 0;
        size = 0;
        root = -1;
    }
}

template <class T>
TArrayList<T>& TArrayList<T>::operator=(const TArrayList<T>& _v)
{
    if (this == &_v)
        return *this;
    if (this->size != _v.size)
    {
        delete[] data;
        delete[] links;

        data = new T[_v.size];
        links = new int[_v.size];
    }
    this->count = _v.count;
    this->size = _v.size;
    this->root = _v.root;
    for (int i = 0; i < size; i++)
    {
        this->links[i] = _v.links[i];
        this->data[i] = _v.data[i];
    }
}

template<class T>
inline void TArrayList<T>::InsFirst(T d)
{
    if (this->IsFull())
        throw - 1;
    int i;
    for (i = 0; i < size; i++)
    {
        if (links[i] == -2)
            break;
    }
    data[i] = d;
    links[i] = root;
    root = i;
    count++;
}

template<class T>
inline void TArrayList<T>::InsLast(T d)
{
    if (this->IsFull())
        throw - 1;
    if (this->IsEmpty())
    {
        root = 0;
        data[0] = d;
        links[0] = -1;
    }
    else
    {
        int i;
        for (i = 0; i < size; i++)
            if (links[i] == -2)
                break;

        int end = root;
        while (links[end] != -1)
            end = links[end];

        data[i] = d;
        links[i] = -1;
        links[end] = i;
    }
    count++;
}

template<class T>
inline void TArrayList<T>::Ins(TArrayListIterator<T>& e, T d)
{
    if (this->IsFull())
        throw - 1;
    if (links[e.index] == -1)
    {
        this->InsLast(d);
    }
    else
    {
        int i;
        for (i = 0; i < size; i++)
        {
            if (links[i] == -2)
                break;
        }
        links[i] = links[e.index];
        links[e.index] = i;
        data[i] = d;
        count++;
    }
}

template<class T>
inline bool TArrayList<T>::IsEmpty(void) const
{
    return count == 0;
}

template<class T>
inline bool TArrayList<T>::IsFull(void) const
{
    return count >= size;
}

template<class T>
inline TArrayListIterator<T> TArrayList<T>::begin()
{
    return TArrayListIterator<T>(*this, root);
}

template<class T>
inline TArrayListIterator<T> TArrayList<T>::end()
{
    return TArrayListIterator<T>(*this, -1);
}

template<class T>
inline T TArrayList<T>::GetFirst()
{
    if (this->IsEmpty())
        throw - 1;
    return data[root];
}

template<class T>
inline T TArrayList<T>::GetLast()
{
    if (this->IsEmpty())
        throw - 1;
    int end = root;
    while (links[end] != -1)
        end = links[end];
    return data[end];
}

template<class T>
inline void TArrayList<T>::DelFirst()
{
    if (this->IsEmpty())
        throw - 1;
    int i = root;
    root = links[root];
    links[i] = -2;
    count--;
}

template<class T>
inline void TArrayList<T>::DelLast()
{
    if (this->IsEmpty())
        throw - 1;
    if (links[root] == -1)
    {
        links[root] = -2;
        root = -1;
    }
    else
    {
        int pEnd = root;
        int end = links[root];
        while (links[end] != -1)
        {
            pEnd = end;
            end = links[end];
        }

        links[pEnd] = -1;
        links[end] = -2;
    }
    count--;
}

template<class T>
inline void TArrayList<T>::Del(TArrayListIterator<T>& e)
{
    if (this->IsEmpty())
        throw - 1;
    if (links[e.index] == -1)
    {
        this->DelLast();
    }
    else if (e.index == root)
    {
        this->DelFirst();
    }
    else
    {
        int i;
        for (i = 0; i < size; i++)
        {
            if (links[i] == e.index)
                break;
        }

        links[i] = links[e.index];
        links[e.index] = -2;
        count--;
    }
}

template<class T>
inline int TArrayList<T>::GetCount()
{
    return count;
}

template <class T1>
ostream& operator<<(ostream& ostr, const TArrayList<T1>& A) {
    if (A.IsEmpty())
        return ostr;
    int i = A.root;
    while (A.links[i] != -1)
    {
        ostr << A.data[i];
        i = A.links[i];
    }
    return ostr;
}

template <class T1>
istream& operator>>(istream& istr, TArrayList<T1>& A) {
    if (A.IsFull())
        throw - 1;
    int count;
    istr >> count;
    for (int i = 0; i < count; i++)
    {
        T1 d;
        istr >> d;
        A.InsLast(d);
    }
    return istr;
}

template<class T1>
inline ofstream& operator<<(ofstream& ofstr, TArrayList<T1>& A)
{
    if (A.IsEmpty())
        return ofstr;
    for (TArrayListIterator<int> iter = A.begin(); iter != A.end(); ++iter)
        ofstr << *iter;
    return ofstr;
}

template<class T>
vector<int> TArrayList<T>::ElemsModZero(int n) // Доп. задание 3
{
    vector<int> res;
    if (this->IsEmpty())
        return res;
    for (TArrayListIterator<int> iter = this->begin(); iter != this->end(); ++iter)
        if (*iter % n == 0)
            res.push_back(*iter);
    return res;
}

template<class T>
inline void TArrayList<T>::WriteToFile(string filename) // Доп. задание 2
{
    ofstream fout(filename.c_str());
    fout << *this;
    fout.close();
}
