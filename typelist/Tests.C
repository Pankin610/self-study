#include <iostream>
#include <type_traits>
#include <typeinfo>
#include "TypeList.H"
#include "Erase.H"
#include "Length.H"
#include "IndexOf.H"
#include "SortedBySize.H"
#include "WithoutDuplicates.H"
#include <memory>

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

struct Component{};

struct PolicyA{};
struct PolicyB{};

template<class Policy>
class SomeComp : public Component, public Policy
{
public:

};

typedef TypeList<PolicyA, TypeList<PolicyB, NullType> > PolicyList;

template<class Policies>
struct Matcher
{
    std::unique_ptr<Component> get_comp_with_policy(const std::string& policy_name);
};

template<>
struct Matcher<NullType>
{
    std::unique_ptr<Component> get_comp_with_policy(const std::string& policy_name)
    {
        return nullptr;
    }
};

template<class U, class Next>
struct Matcher< TypeList<U, Next> >
{
    std::unique_ptr<Component> get_comp_with_policy(const std::string& policy_name)
    {
        U* u = nullptr;
        if (policy_name == typeid(u).name())
        {
            return std::make_unique< SomeComp<U> >();
        }
        else
        {
            Matcher<Next> matcher;
            return matcher.get_comp_with_policy(policy_name);
        }
    }

};



int main()
{
    std::unique_ptr<Component> comp = Matcher<PolicyList>().get_comp_with_policy("F7PolicyAvE");
    std::cout << comp.get() << std::endl;
    std::cout << typeid(PolicyA()).name() << std::endl;
    return 0;
}