#include "benchmark/benchmark.h"

#include "SmallObjAllocator.H"
#include <exception>
#include <random>
#include <iostream>

std::vector<void*> alloc_objs;
std::vector<bool> operation_is_alloc;
std::vector<size_t> ind;

static size_t BLOCK_SIZE = 64;
static unsigned char CHUNK_SIZE = 100;

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

    size_t obj_size = 64;
    SmallObjAllocator allocator(BLOCK_SIZE);
    std::vector<void*> alloc_objs;

    size_t i = 0;
    for (auto _ : state)
    {
        assert(i < operation_is_alloc.size());
        assert(ind[i] < alloc_objs.size() || alloc_objs.size() == 0);
        if (operation_is_alloc[i])
        {
            alloc_objs.push_back(allocator.Allocate(obj_size));
        }
        else
        {
            allocator.Deallocate(alloc_objs[ind[i]], obj_size);
            std::swap(alloc_objs[ind[i]], alloc_objs.back());
            alloc_objs.pop_back();
        }
        i++;
    }
}

static void allocate_and_deallocate(benchmark::State& state)
{
    size_t obj_size = 64;
    SmallObjAllocator allocator(CHUNK_SIZE);
    for (auto _ : state)
    {
        allocator.Deallocate(allocator.Allocate(obj_size), BLOCK_SIZE);
    }
}

static void allocate_a_lot_and_deallocate_in_order(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::vector<void*> objs;
        objs.reserve(10000);
        SmallObjAllocator allocator(100);
        for (size_t i = 0; i < 10000; i++)
        {
            objs.push_back(allocator.Allocate(64));
        }
        for (void* ptr : objs)
        {
            allocator.Deallocate(ptr, 64);
        }
    }
}

static void allocate_a_lot_and_deallocate_in_reverse_order(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::vector<void*> objs;
        objs.reserve(10000);
        SmallObjAllocator allocator(100);
        for (size_t i = 0; i < 10000; i++)
        {
            objs.push_back(allocator.Allocate(64));
        }
        for (size_t i = 0; i < objs.size(); i++)
        {
            allocator.Deallocate(objs[objs.size() - 1 - i], 64);
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