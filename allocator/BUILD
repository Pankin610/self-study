cc_library(
    name = "allocator",
    srcs = [
        "Chunk.H",
        "FixedAllocator.H",
        "SmallObjAllocator.H",
        "Chunk.C",
        "FixedAllocator.C",
        "SmallObjAllocator.C"
    ]
)

load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "benchmark",
    srcs = ["benchmark.C"],
    copts = ["-Iexternal/benchmark/include"],
    deps = [
        ":allocator",
        "@benchmark//:benchmark_main",
    ],
)

cc_test(
    name = "benchmark_default_allocator",
    srcs = ["benchmark_default_allocator.C"],
    copts = ["-Iexternal/benchmark/include"],
    deps = [
        "@benchmark//:benchmark_main",
    ],
)

cc_binary(
    name = "tests",
    srcs = ["Tests.C"],
    deps = [
        ":allocator"
    ]
)