#include <benchmark/benchmark.h>

#include <algorithm>
#include <random>
#include <vector>

#include "sorting_algos.hpp"

#define REPEAT2(X) X X
#define REPEAT4(X) REPEAT2(REPEAT2(X))
#define REPEAT16(X) REPEAT4(REPEAT4(X))
#define REPEAT(X) REPEAT4(REPEAT16(X))

auto constexpr n_repetitions = 64;

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

template <typename SortType>
static void BM_Sort(benchmark::State& state) {
  auto size = state.range(0);

  auto n_randomized = size * n_permutations;
  auto random_vector = std::vector<int>(n_randomized);
  std::iota(random_vector.begin(), random_vector.end(), 0);
  auto gen = std::mt19937(0);
  std::shuffle(random_vector.begin(), random_vector.end(), gen);

  auto vector_copy = std::vector<int>(size);
  for (auto _ : state) {
    auto permutation_begin = random_vector.begin();
    while (permutation_begin != random_vector.end()) {
      auto permutation_end = permutation_begin + size;

      auto data = vector_copy.data();
      benchmark::DoNotOptimize(data);
      REPEAT(std::copy(permutation_begin, permutation_end, vector_copy.begin());
             benchmark::ClobberMemory();
             SortType::sort(vector_copy.begin(), vector_copy.end());
             benchmark::ClobberMemory();)

      permutation_begin = permutation_end;
    }
  }

  auto total_items = n_randomized * n_repetitions;
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
