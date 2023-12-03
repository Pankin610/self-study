#pragma once

#include <iostream>

struct NullType
{};

template<class T, class Next>
struct TypeList
{
    typedef T value;
    typedef Next next_node;
};