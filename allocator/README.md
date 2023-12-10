64 byte objects and chunks of 100 blocks:
|Benchmark                                                        |        Time   |          CPU |  Iterations|
|-----------------------------------------------------------------|---------------|--------------|------------|
|                                                                 |               |              |            |
|random_alloc_and_dealloc/iterations:10000000                     |      109 ns   |       109 ns |    10000000|
|allocate_and_deallocate/iterations:10000000                      |     27.1 ns   |      27.1 ns |    10000000|
|allocate_a_lot_and_deallocate_in_order/iterations:10000          |   543909 ns   |    543870 ns |       10000|
|allocate_a_lot_and_deallocate_in_reverse_order/iterations:10000  |   541802 ns   |    541717 ns |       10000|

Deleting a chunk even if it's the last one:
|Benchmark                                                        |        Time   |          CPU |  Iterations|
|-----------------------------------------------------------------|---------------|--------------|------------|
|                                                                 |               |              |            |
|random_alloc_and_dealloc/iterations:10000000                     |      110 ns   |       110 ns |    10000000|
|allocate_and_deallocate/iterations:10000000                      |      300 ns   |       300 ns |    10000000|
|allocate_a_lot_and_deallocate_in_order/iterations:10000          |   534385 ns   |    534382 ns |       10000|
|allocate_a_lot_and_deallocate_in_reverse_order/iterations:10000  |   531800 ns   |    531775 ns |       10000|

The second case becomes 11 times slower.

Not using the last chunk heuristic:
|Benchmark                                                        |        Time   |          CPU |  Iterations|
|-----------------------------------------------------------------|---------------|--------------|------------|
|                                                                 |               |              |            |
|random_alloc_and_dealloc/iterations:10000000                     |      116 ns   |       116 ns |    10000000|
|allocate_and_deallocate/iterations:10000000                      |     31.6 ns   |      31.6 ns |    10000000|
|allocate_a_lot_and_deallocate_in_order/iterations:10000          |  2679640 ns   |   2677834 ns |       10000|
|allocate_a_lot_and_deallocate_in_reverse_order/iterations:10000  |  3659392 ns   |   3659195 ns |       10000|

The last two cases are over 5 times slower.


Smaller chunks, 10 blocks per each:
|Benchmark                                                        |        Time   |          CPU |  Iterations|
|-----------------------------------------------------------------|---------------|--------------|------------|
|                                                                 |               |              |            |
|random_alloc_and_dealloc/iterations:10000000                     |      111 ns   |       111 ns |    10000000|
|allocate_and_deallocate/iterations:10000000                      |     26.8 ns   |      26.8 ns |    10000000|
|allocate_a_lot_and_deallocate_in_order/iterations:10000          |  2713287 ns   |   2709256 ns |       10000|
|allocate_a_lot_and_deallocate_in_reverse_order/iterations:10000  |  3717075 ns   |   3713058 ns |       10000|

Bigger chunks, 255 blocks per each:
|Benchmark                                                        |        Time   |          CPU |  Iterations|
|-----------------------------------------------------------------|---------------|--------------|------------|
|                                                                 |               |              |            |
|random_alloc_and_dealloc/iterations:10000000                     |      111 ns   |       111 ns |    10000000|
|allocate_and_deallocate/iterations:10000000                      |     27.5 ns   |      27.6 ns |    10000000|
|allocate_a_lot_and_deallocate_in_order/iterations:10000          |   508487 ns   |    508479 ns |       10000|
|allocate_a_lot_and_deallocate_in_reverse_order/iterations:10000  |   490214 ns   |    490193 ns |       10000|


Bigger objects, 128 bytes:
|Benchmark                                                        |        Time   |          CPU |  Iterations|
|-----------------------------------------------------------------|---------------|--------------|------------|
|                                                                 |               |              |            |
|random_alloc_and_dealloc/iterations:10000000                     |     89.3 ns   |      89.3 ns |    10000000|
|allocate_and_deallocate/iterations:10000000                      |     26.9 ns   |      26.9 ns |    10000000|
|allocate_a_lot_and_deallocate_in_order/iterations:10000          |   531936 ns   |    531900 ns |       10000|
|allocate_a_lot_and_deallocate_in_reverse_order/iterations:10000  |   536928 ns   |    536919 ns |       10000|

Smaller objects, 4 bytes:
|Benchmark                                                        |        Time   |          CPU |  Iterations|
|-----------------------------------------------------------------|---------------|--------------|------------|
|                                                                 |               |              |            |
|random_alloc_and_dealloc/iterations:10000000                     |     854 ns    |      854 ns  |    10000000|
|allocate_and_deallocate/iterations:10000000                      |     26.7 ns   |      26.7 ns |    10000000|
|allocate_a_lot_and_deallocate_in_order/iterations:10000          |   530457 ns   |    530450 ns |       10000|
|allocate_a_lot_and_deallocate_in_reverse_order/iterations:10000  |   530838 ns   |    530382 ns |       10000|

Default allocator:
|-----------------------------------------------------------------|---------------|--------------|------------|
|Benchmark                                                        |        Time   |          CPU |  Iterations|
|-----------------------------------------------------------------|---------------|--------------|------------|
|                                                                 |               |              |            |
|random_alloc_and_dealloc/iterations:10000000                     |     53.5 ns   |      53.5 ns |    10000000|
|allocate_and_deallocate/iterations:10000000                      |     20.8 ns   |      20.8 ns |    10000000|
|allocate_a_lot_and_deallocate_in_order/iterations:10000          |   644920 ns   |    644910 ns |       10000|
|allocate_a_lot_and_deallocate_in_reverse_order/iterations:10000  |   596027 ns   |    596019 ns |       10000|