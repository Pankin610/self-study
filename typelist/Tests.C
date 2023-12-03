#include <iostream>
#include <type_traits>
#include "TypeList.H"
#include "Erase.H"
#include "Length.H"
#include "IndexOf.H"
#include "SortedBySize.H"
#include "WithoutDuplicates.H"

typedef TypeList<char,
    TypeList<unsigned char,
        TypeList<signed char, NullType >
    >
> CharList;

static_assert(Length<CharList>::value == 3);
static_assert(IndexOf<int, CharList>::value == -1);
static_assert(IndexOf<char, CharList>::value == 0);

typedef Erase<unsigned char, CharList>::Result SignedCharList;
static_assert(Length<SignedCharList>::value == 2);
static_assert(IndexOf<unsigned char, SignedCharList>::value == -1);

static_assert(IsSmaller<char, int>::value);
static_assert(IsSmaller<char, NullType>::value);
static_assert(IsSmaller<double, NullType>::value);

typedef TypeList<double,
    TypeList<int,
        TypeList<char, NullType >
    >
> Numbers;

static_assert(std::is_same<SmallestSizeElement<Numbers>::Result, char>::value);

typedef SortedBySize<Numbers>::Result NumbersSortedBySize;
static_assert(IndexOf<char, NumbersSortedBySize>::value == 0);
static_assert(IndexOf<int, NumbersSortedBySize>::value == 1);
static_assert(IndexOf<double, NumbersSortedBySize>::value == 2);

typedef TypeList<char,
    TypeList<unsigned char,
        TypeList<signed char,
            TypeList<signed char,
                TypeList<char, NullType > > >
    >
> CharListWithDuplicates;

static_assert(Length<CharListWithDuplicates>::value == 5);
static_assert(Length< WithoutDuplicates<CharListWithDuplicates>::Result >::value == 3);

int main()
{

    return 0;
}