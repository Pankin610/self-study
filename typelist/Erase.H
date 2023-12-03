#pragma once
#include "TypeList.H"

template<typename T, class TypeList>
struct Erase;

template<typename T>
struct Erase<T, NullType>
{
    typedef NullType Result;
};

template<typename T, class U, class Next>
struct Erase<T, TypeList<U, Next> >
{
    typedef typename std::conditional<std::is_same<T, U>::value, Next, TypeList<U, typename Erase<T, Next>::Result > >::type Result;
};

template<typename T, class TypeList>
struct EraseAll;

template<typename T>
struct EraseAll<T, NullType>
{
    typedef NullType Result;
};

template<typename T, class U, class Next>
struct EraseAll<T, TypeList<U, Next> >
{
    typedef typename std::conditional<std::is_same<T, U>::value, typename EraseAll<T, Next>::Result, TypeList<U, typename EraseAll<T, Next>::Result > >::type Result;
};