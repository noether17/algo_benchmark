#include <benchmark/benchmark.h>

#include <algorithm>
#include <random>
#include <vector>

#include "sorting_algos.hpp"

auto constexpr min_array_size = 1 << 0;
auto constexpr max_array_size = 1 << 10;

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

auto constexpr n_permutations = 64;
auto constexpr n_repetitions = 64;

template <typename SortType>
static void BM_Sort(benchmark::State& state) {
  auto size = state.range(0);

  auto n_randomized = size * n_permutations;
  auto random_vector = std::vector<int>(n_randomized);
  std::iota(random_vector.begin(), random_vector.end(), 0);
  auto gen = std::mt19937(0);
  std::shuffle(random_vector.begin(), random_vector.end(), gen);

  auto total_items = n_randomized * n_repetitions;
  auto v = std::vector<int>{};
  v.reserve(total_items);
  for (auto i = 0; i < n_repetitions; ++i) {
    v.insert(v.end(), random_vector.begin(), random_vector.end());
  }

  for (auto _ : state) {
    auto data = v.data();
    benchmark::DoNotOptimize(data);
    auto segment_begin = v.begin();
    while (segment_begin != v.end()) {
      auto segment_end = segment_begin + size;
      SortType::sort(segment_begin, segment_end);
      segment_begin = segment_end;
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
