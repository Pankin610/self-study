#include <iostream>
#include <type_traits>

struct NullType
{};

template<class T, class Next>
struct TypeList
{
    typedef T value;
    typedef Next next_node;
};

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

typedef TypeList<char,
    TypeList<unsigned char,
        TypeList<signed char, NullType >
    >
> CharList;

static_assert(Length<CharList>::value == 3);
static_assert(IndexOf<int, CharList>::value == -1);
static_assert(IndexOf<char, CharList>::value == 0);

int main()
{

    return 0;
}