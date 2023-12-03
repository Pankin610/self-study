#pragma once
#include "TypeList.H"
#include "Erase.H"

template<class TypeList>
struct SmallestSizeElement;

template<>
struct SmallestSizeElement<NullType>
{
    typedef NullType Result;
};

template <class A, class B>
struct IsSmaller
{
    static const bool value = (sizeof(A) < sizeof(B) && !std::is_same<A, NullType>::value) || std::is_same<B, NullType>::value;
};

template<class U, class Next>
struct SmallestSizeElement< TypeList<U, Next> >
{
private:
    typedef typename SmallestSizeElement<Next>::Result _next_smallest;
public:
    typedef typename std::conditional< IsSmaller<U, _next_smallest>::value, U, _next_smallest >::type Result;
};

template<class TypeList>
struct SortedBySize;

template<>
struct SortedBySize<NullType>
{
    typedef NullType Result;
};

template<class U, class Next>
struct SortedBySize< TypeList<U, Next> >
{
private:
    typedef TypeList<U, Next> _list;
    typedef typename SmallestSizeElement<_list>::Result _smallest_element;
public:
    typedef TypeList<_smallest_element, typename SortedBySize< typename Erase<_smallest_element, _list>::Result >::Result > Result;
};