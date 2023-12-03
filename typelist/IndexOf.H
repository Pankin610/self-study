#pragma once
#include "TypeList.H"

template<typename T, class TypeList>
struct IndexOf;

template<typename T>
struct IndexOf<T, NullType>
{
    static const int value = -1;
};

template<typename T, class U, class V>
struct IndexOf<T, TypeList<U, V> >
{
    static const int value = std::is_same<T, U>::value ? 0 : (IndexOf<T, V>::value == -1 ? -1 : IndexOf<T, V>::value + 1);
};