#include <benchmark/benchmark.h>

#include <algorithm>
#include <random>
#include <vector>

#include "sorting_algos.hpp"

// #define REPEAT2(X) X X
// #define REPEAT4(X) REPEAT2(X) REPEAT2(X)
// #define REPEAT8(X) REPEAT4(X) REPEAT4(X)
// #define REPEAT16(X) REPEAT8(X) REPEAT8(X)
// #define REPEAT(X) REPEAT16(X) REPEAT16(X)

auto constexpr n_repetitions = 1024;
auto constexpr min_array_size = 1 << 0;
auto constexpr max_array_size = 1 << 10;
auto constexpr total_items = n_repetitions * max_array_size;

struct NoSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    no_sort(first, last);
  }
};

struct InsertionSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    insertion_sort(first, last);
  }
};

struct InsertionSorter2 {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    insertion_sort_2(first, last);
  }
};

struct BubbleSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    bubble_sort(first, last);
  }
};

struct QuickSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    quick_sort(first, last);
  }
};

struct HeapSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    heap_sort(first, last);
  }
};

template <typename SortType>
static void BM_Sort(benchmark::State& state) {
  auto size = state.range(0);
  auto gen = std::mt19937(0);
  auto v = std::vector<int>(total_items);
  std::iota(v.begin(), v.end(), 0);
  std::shuffle(v.begin(), v.end(), gen);

  for (auto _ : state) {
    auto data = v.data();
    benchmark::DoNotOptimize(data);
    for (auto iter = v.begin(); iter != v.end(); iter += size) {
      SortType::sort(iter, iter + size);
    }
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(total_items);
}

BENCHMARK_TEMPLATE(BM_Sort, NoSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);
BENCHMARK_TEMPLATE(BM_Sort, InsertionSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);
BENCHMARK_TEMPLATE(BM_Sort, InsertionSorter2)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);
BENCHMARK_TEMPLATE(BM_Sort, BubbleSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);
BENCHMARK_TEMPLATE(BM_Sort, QuickSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);
BENCHMARK_TEMPLATE(BM_Sort, HeapSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);
