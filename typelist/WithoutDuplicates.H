#pragma once

#include "TypeList.H"
#include "Erase.H"

template<class TypeList>
class WithoutDuplicates;

template<>
struct WithoutDuplicates<NullType>
{
    typedef NullType Result;
};

template<class U, class Next>
struct WithoutDuplicates< TypeList<U, Next> >
{
    typedef TypeList<U, typename WithoutDuplicates<typename EraseAll<U, Next>::Result>::Result> Result;
};