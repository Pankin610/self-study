#include "benchmark/benchmark.h"

#include <exception>
#include <random>
#include <iostream>

std::vector<void*> alloc_objs;
std::vector<bool> operation_is_alloc;
std::vector<size_t> ind;

static size_t BLOCK_SIZE = 64;

static void DoSetup(const benchmark::State& state)
{
    std::mt19937 rng(610);
    size_t num_objs = 0;
    for (size_t i = 0; i < 10000000; i++)
    {
        operation_is_alloc.push_back(rng() % 2);
        ind.push_back(num_objs ? rng() % num_objs : 0);
        if (operation_is_alloc.back())
        {
            num_objs++;
        }
        else
        {
            if (num_objs == 0)
            {
                operation_is_alloc.back() = true;
            }
            else
            {
                num_objs--;
            }
        }

    }
    alloc_objs.reserve(10000);
}

static void DoTeardown(const benchmark::State& state)
{
    alloc_objs.clear();
    operation_is_alloc.clear();
    ind.clear();
}

static void random_alloc_and_dealloc(benchmark::State& state)
{
    assert(operation_is_alloc.size() == ind.size());

    std::vector<void*> alloc_objs;

    size_t i = 0;
    for (auto _ : state)
    {
        assert(i < operation_is_alloc.size());
        assert(ind[i] < alloc_objs.size() || alloc_objs.size() == 0);
        if (operation_is_alloc[i])
        {
            alloc_objs.push_back(new char[BLOCK_SIZE]);
        }
        else
        {
            delete (char*)alloc_objs[ind[i]];
            std::swap(alloc_objs[ind[i]], alloc_objs.back());
            alloc_objs.pop_back();
        }
        i++;
    }
}

static void allocate_and_deallocate(benchmark::State& state)
{
    for (auto _ : state)
    {
        delete new char[BLOCK_SIZE];
    }
}

static void allocate_a_lot_and_deallocate_in_order(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::vector<char*> objs;
        objs.reserve(10000);
        for (size_t i = 0; i < 10000; i++)
        {
            objs.push_back(new char[BLOCK_SIZE]);
        }
        for (char* ptr : objs)
        {
            delete ptr;
        }
    }
}

static void allocate_a_lot_and_deallocate_in_reverse_order(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::vector<char*> objs;
        objs.reserve(10000);
        for (size_t i = 0; i < 10000; i++)
        {
            objs.push_back(new char[BLOCK_SIZE]);
        }
        for (size_t i = 0; i < objs.size(); i++)
        {
            delete objs[objs.size() - 1 - i];
        }
    }
}

BENCHMARK(random_alloc_and_dealloc)->Iterations(10000000)->Setup(DoSetup)->Teardown(DoTeardown);
BENCHMARK(allocate_and_deallocate)->Iterations(10000000);
BENCHMARK(allocate_a_lot_and_deallocate_in_order)->Iterations(10000);
BENCHMARK(allocate_a_lot_and_deallocate_in_reverse_order)->Iterations(10000);

int main(int argc, char** argv) {
    // Run the benchmark
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}