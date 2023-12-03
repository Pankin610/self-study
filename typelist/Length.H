#pragma once
#include "TypeList.H"

template <class TypeList>
struct Length;

template<>
struct Length< NullType >
{
    static const size_t value = 0;
};

template<class T, class Next>
struct Length< TypeList< T, Next > >
{
    static const size_t value = Length< Next >::value + 1;
};
